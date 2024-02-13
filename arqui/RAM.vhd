

		-- Programa para el manejo de sistema de memoria
		-- Usando una SDRAM de 64MB
		-- Elaborado por:  U581
		--	Fecha:  30 de Octubre de 2020
		
		
		        -- Declaracion de Bibliotecas
				  
				Library ieee;
		      use ieee.std_logic_1164.all;
				use work.bcd_7seg.all;
				
				
				entity RAM is 
					Port(
							clk, clr  	: 		  in std_logic;    							-- Reloj, Reset 
							rd, wr 		:		  in std_logic;							   -- seleccion de operacion
							ent_datos   : 		  in std_logic_vector(7 downto 0);		-- Datos de los switches
							bus_datos   :       inout std_logic_vector(7 downto 0);  -- Bus de datos
							ent_dir 		: 		  in std_logic_vector(3 downto 0);		--	Dir de los switches
							bus_dir     :       out std_logic_vector(12 downto 0);	-- Bus de direcciones 13 bits
							bus_ctrl		:		  out std_logic_vector(11 downto 0);	-- Bus de Control
							Disp_7sg    : 	     out std_logic_vector(13 downto 0)    -- Despliegue en 7 segmentos
						 );    
			   end entity;
				
				
				architecture sys_RAM of  RAM is
				
				 
		   
				   begin
		         
					    
				REG : process(clk,clr,bus_datos,rd,wr,ent_datos)  -- Proceso para instrucciones secuenciales
                
			         					 	 
						begin
			
						  if (clr = '0') then          	   -- Si se da el reset
			             
							   bus_ctrl <= "000000000000";   -- Reset del bus de control
										    
						  elsif (clk' event and clk = '1') then     	-- Inicio del programa
						  
						     						    
							  if (rd = '0') then                   -- si RD/WR# es 1 la operacion es de lectura
							  
							  bus_ctrl (0) <= '1'; 							-- Seleccionando banco de memoria 0
							  bus_ctrl (1) <= '0'; 							-- Seleccionando banco de memoria 1
							  bus_ctrl (2) <= '1'; 							--	Activa la mascara 0 de RAM
							  bus_ctrl (3) <= '0'; 							--	Desactiva mascara 1
							  bus_ctrl (4) <= '0'; 							-- Desactiva mascara 2
							  bus_ctrl (5) <= '0'; 							-- Desactiva mascara 3
							  bus_ctrl (6) <= '1';							-- Desactiva el estrobo de direccion de fila
							  bus_ctrl (7)	<= '1';							-- Activa el estrobo de direccion de columna
							  bus_ctrl (8)	<= '1';							-- Activa el rejol de la RAM
							  bus_ctrl (9) <= clk;							-- Conmutacion de reloj a RAM						
							  bus_ctrl (10)<= '1';							--	Escritura desactivada
							  bus_ctrl (11)<= '1';							-- Chip enable de la ram activado
							  
							  bus_dir (10) <= '0';							-- A10 del bus de direccion en 1 para pre-carga
							  
		                 bus_dir(12 downto 4) <= "000000000";		-- Direcciones no usadas se ponen en 0
							  bus_dir(3 downto 0) <= ent_dir;			-- Direccion a leer					  
							  
							  bcd_conv(bus_datos (3 downto 0),Disp_7sg(6  downto 0));   -- Mostrando el primer  nibble
							  bcd_conv(bus_datos (7 downto 4),Disp_7sg(13 downto 7));   -- Mostrando el segundo nibble
							  							  							  
							  end if;
							  
																					-- Si es escritura
							  
							  if (wr = '0') then
							  
							  bus_ctrl (0) <= '1'; 							-- Seleccionando banco de memoria 0
							  bus_ctrl (1) <= '0'; 							-- Seleccionando banco de memoria 1
							  bus_ctrl (2) <= '1'; 							--	Activa la mascara 0 de RAM
							  bus_ctrl (3) <= '0'; 							--	Desactiva mascara 1
							  bus_ctrl (4) <= '0'; 							-- Desactiva mascara 2
							  bus_ctrl (5) <= '0'; 							-- Desactiva mascara 3
							  bus_ctrl (6) <= '1';							-- Desactiva el estrobo de direccion de fila
							  bus_ctrl (7)	<= '1';							-- Activa el estrobo de direccion de columna
							  bus_ctrl (8)	<= '1';							-- Activa el rejol de la RAM
							  bus_ctrl (9)	<= clk;						   -- Conmutacion de reloj a RAM						
							  bus_ctrl (10)<= '0';							--	Escritura activada
							  bus_ctrl (11)<= '1';							-- Chip enable de la ram activado
							  
							  bus_dir (10) <= '0';							-- A10 del bus de direccion en 1 para pre-carga
							  
		                 bus_dir(12 downto 4) <= "000000000";		-- Direcciones no usadas se ponen en 0
							  bus_dir(3 downto 0) <= ent_dir;			-- Direccion a leer	
										  
							  
							  bus_datos <= ent_datos;						-- Escribiendo datos en la RAM						
							  	  
							  
							  end if;                                 -- Fin del IF para control de escritura/lectura
							  						
						  end if;		  										-- Fin del IF para reloj
		 		
	         end process REG;												-- Fin del proceso

            end sys_RAM;													--	Fin de la Arquitectura
