
			--	Programa de Unidad de Control, con 8 instrucciones para una arquitectura de 8 bits 
			-- Elaborado por: U581
			--	Fecha: 5 de Noviembre de 2020
			
			
         -- Declaracion de Bibliotecas
					  
			library ieee;
			use ieee.std_logic_1164.all;
			use ieee.std_logic_unsigned.all;   -- Esta biblioteca es usada para operaciones con signo
			use ieee.numeric_std.all;
			use work.ALU_UC.all;					-- Paquete de los registros
			use work.bcd_7seg.all;				--	Paquete para los display
			
			
						--	Inicio de la entidad
						
			entity U_Control is 					
					Port(
							clk, clr  	: 		  in std_logic;    							-- Reloj, Reset 
							exe 		   :		  in std_logic;							   -- Boton de ejecucion
							ent_datos   : 		  in std_logic_vector(7 downto 0);		-- Datos de los switches
							ent_inst		:		  in std_logic_vector(2 downto 0);		--	Intrucciones del Switch	
							bus_datos   :       inout std_logic_vector(7 downto 0);  -- Bus de datos
							flag			:		  out std_logic_vector (2 downto 0);	-- Banderas de estado
							bus_dir		:		  out std_logic_vector(12 downto 0);	-- Bus de direcciones 13 bits
							bus_ctrl		:		  out std_logic_vector(11 downto 0);	-- Bus de Control
							Disp_7sg    : 	     out std_logic_vector(55 downto 0)    -- Despliegue en 7 segmentos para todos los display
						 );    
			end entity;
			
			
			architecture control of  U_Control is
			
								-- Creacion de los registros
		  
				signal AX         : std_logic_vector (15 downto 0) := "0000000000000000";  -- Reg. Acumulador
				signal PC		   : unsigned(7 downto 0) 				:= "00000000";   			-- Reg. contador de programa
				signal IX	      : std_logic_vector (12 downto 0) := "0000000000000";		-- Reg. Indice
				signal inst       : std_logic_vector(3 downto 0) := "0000";			 			-- zero
				signal aux			: std_logic_vector(7 downto 0) := "00000000";				-- auxiliar
							
				begin
				
				UC : process(clk,clr,exe,ent_datos,ent_inst) 
				     
					  begin 
					 
					  if (clr = '0') then          	-- Si se da el reset
			
						AX <= "0000000000000000";     -- Limpia el acumulador de 16 bits
						PC <= "00000000";					-- Limpia el contador de programa
						IX <= "0000000000000";		   -- Limpia el indice
		    
					  elsif (clk' event and clk = '1') then
					 
					 	 if (exe = '0') then									--	Fue presionado el boton de la ejecucion de instrucciones
					 
						   case ent_inst is									--	Set de instrucciones
							  
							  when "000" =>									-- Instruccion CLA
							  
								AX <= "0000000000000000";					-- Limpia el acumulador 
								PC <= PC + 1;									-- Incremento del contador de programa 
							     
							  when "001" =>									-- MOVX
							  
								AX(7 downto 0) <= ent_datos;				-- Carga la parte baja del acumulador con un dato
								PC <= PC + 1;			 					   -- Incremento del contador de programa
							  
							  when "010" =>									-- MOVIX
							  
								IX (7 downto 0) <= ent_datos;					-- Carga el registro indice con una direccion
								
								bus_ctrl (0) <= '0'; 						-- Configurando banco de memoria 0
								bus_ctrl (1) <= '0'; 						-- Configurando banco de memoria 1
								
								bus_ctrl (2) <= '0'; 						--	Activa la mascara 0 de RAM
								bus_ctrl (3) <= '0'; 						--	Desactiva mascara 1
								bus_ctrl (4) <= '0'; 						-- Desactiva mascara 2
								bus_ctrl (5) <= '0'; 						-- Desactiva mascara 3
								
								bus_ctrl (6) <= '1';							-- Seleccion de fila
								bus_ctrl (7) <= '0';							-- Seleccion de columnax
								
								bus_ctrl (8) <= '1';							-- Activa el rejol de la RAM
								bus_ctrl (9) <= clk;							-- Conmutacion de reloj a RAM	
								
								bus_ctrl (10)<= '1';							--	Escritura desactivada
								bus_ctrl (11)<= '1';							-- Chip enable de la ram activado
							  
								bus_dir (10) <= '1';							-- A10 del bus de direccion en 1 para pre-carga
							  
								bus_dir <= IX;									-- Se carga la direccion del registro IX
								AX <= std_logic_vector("00000000" & bus_datos) ;	-- Se carga AX con el dato de la direccion IX
																						
								PC <= PC + 1;			   				   -- Incremento del contador de programa
							  
							  when "011" =>									-- MOVIA
							  
								IX (7 downto 0) <= ent_datos;				-- Carga el registro indice con una direccion
								
								bus_ctrl (0) <= '0'; 						-- Configurando banco de memoria 0
								bus_ctrl (1) <= '0'; 						-- Configurando banco de memoria 1
								
								bus_ctrl (2) <= '0'; 						--	Activa la mascara 0 de RAM
								bus_ctrl (3) <= '0'; 						--	Desactiva mascara 1
								bus_ctrl (4) <= '0'; 						-- Desactiva mascara 2
								bus_ctrl (5) <= '0'; 						-- Desactiva mascara 3
								
								bus_ctrl (6) <= '1';							-- Seleccion de fila
								bus_ctrl (7) <= '0';							-- Seleccion de columna
								
								bus_ctrl (8) <= '1';							-- Activa el rejol de la RAM
								bus_ctrl (9) <= clk;							-- Conmutacion de reloj a RAM	
								
								bus_ctrl (10)<= '0';							--	Escritura activada
								bus_ctrl (11)<= '1';							-- Chip enable de la ram activado
							  
								bus_dir (10) <= '1';							-- A10 del bus de direccion en 1 para pre-carga
							  
								bus_dir <= IX;									-- Se carga la direccion del registro IX
								bus_datos <= AX (7 downto 0);				-- Se carga en la direccion de memoria el dato en AX
								
								PC <= PC + 1;			 					   -- Incremento del contador de programa							
							  
							  when "100" =>									-- ADD
							 
							     -- Suma del acumulador con un dato y el resultado se almacena en el acumulador
								
								ADD(AX(7 downto 0),ent_datos,flag, AX(7 downto 0));								
								PC <= PC + 1;			 					   -- Incremento del contador de programa	
							  
							  when "101" =>									-- SUB
							    
								  -- Resta del acumulador con un dato y el resultado se almacena en el acumulador 
								
								SUB(AX(7 downto 0), ent_datos,flag, AX(7 downto 0));												
								PC <= PC + 1;			 					   -- Incremento del contador de programa
							  
							  when "110" =>				   				-- MUL
							  
							     -- Multiplica el acumulador con un dato y el resultado se almacena en el acumulador
								
								MUL(AX(7 downto 0),ent_datos,flag,AX);												
								PC <= PC + 1;								   -- Incremento del contador de programa
							  
							  when others =>									-- OR
							  
							     -- OR del acumulador con un dato y el resultado se almacena en el acumulador
							  
								LOR(AX(7 downto 0),ent_datos,flag,AX(7 downto 0));												
								PC <= PC + 1;			 					   -- Incremento del contador de programa
							  
							
							end case;
					 					 
						 else
						 
						               -- Mostrando el Contador de programa
						     
							  aux <= std_logic_vector(PC);
							  bcd_conv(aux (3 downto 0),Disp_7sg(48 downto 42));   -- Mostrando el primer  nibble
   						  bcd_conv(aux (7 downto 4),Disp_7sg(55 downto 49));   -- Mostrando el segundo nibble
							  
											--	Mostrando el registro indice
											
							  bcd_conv(IX (3 downto 0),Disp_7sg(34 downto 28));   -- Mostrando el primer  nibble
   						  bcd_conv(IX (7 downto 4),Disp_7sg(41 downto 35));   -- Mostrando el segundo nibble
											
											-- Mostrando el codigo de la instruccion
											
							  inst <= std_logic_vector('0' & ent_inst);
							  bcd_conv(inst,Disp_7sg(20 downto 14));   -- Mostrando el primer  nibble (REVISAR)
   						  inst <= "0000";
							  bcd_conv(inst,Disp_7sg(27 downto 21));   				     -- Mostrando el segundo nibble
								
											-- Mostrando el dato en el acumulador
							  
							  bcd_conv(AX(3 downto 0),Disp_7sg(6 downto  0));   -- Mostrando el primer  nibble 
   						  bcd_conv(AX(7 downto 4),Disp_7sg(13 downto 7));   -- Mostrando el segundo nibble
											
			
													
						 end if;													
					  end if;													--	Fin del primer if del CLK
				
				end process UC;
				
				
				
			end architecture;
		         