
   -- Paquete de la ALU para SUMA, RESTA, MULTIPLICACION en operaciones aritmeticas
	-- Para OR, AND, XOR y NOT para operaciones Logicas
	
	-- Elaborado por:   U581
	-- Fecha: 30 de octubre de 2020
	
	              -- Declaracion de Bibliotecas
					  
			library ieee;
			use ieee.std_logic_1164.all;
			use ieee.std_logic_signed.all;          -- Esta biblioteca es usada para operaciones con signo
			use ieee.numeric_std.all;
			
			
			         -- Declaracion de la entidad
			
	      package ALU_UC is
			
			    -- Declaracion de constantes
				 
			   signal aux    : std_logic_vector(15 downto 0) := "0000000000000000";  -- registro para revision de Flag
			   constant zero : std_logic_vector(7 downto 0) := "00000000" ;   -- Para 0  
				constant full : std_logic_vector(7 downto 0) := "00001111" ;   -- Para 1
				
				-- Declaracion de procedimientos
				
				-- Suma
				
				procedure ADD (signal REN1 : in std_logic_vector (7 downto 0);   -- Valores de entrada del acumulador
									signal REN2 : in std_logic_vector (7 downto 0);   -- Valores de entrada de los switches
									signal flag : out std_logic_vector (2 downto 0);  -- Banderas de estado
			                  signal A    : out std_logic_vector (7 downto 0)); -- Valor a retornar
									
				-- Resta
				
				procedure SUB (signal REN1 : in std_logic_vector (7 downto 0);   -- Valores de entrada del acumulador
									signal REN2 : in std_logic_vector (7 downto 0);	  -- Valores de entrada de los switches
									signal flag : out std_logic_vector (2 downto 0);  -- Banderas de estado
			                  signal A    : out std_logic_vector (7 downto 0)); -- Valor a retornar
									
				-- Multiplicación
				
				procedure MUL (signal REN1 : in std_logic_vector (7 downto 0);  	-- Valores de entrada del acumulador
									signal REN2 : in std_logic_vector (7 downto 0);  	-- Valores de entrada de los switches
									signal flag : out std_logic_vector (2 downto 0); 	-- Banderas de estado
			                  signal Am   : out std_logic_vector (15 downto 0)); -- Valor a retornar
				
				-- División				
									
				procedure DIVI (signal REN1 : in std_logic_vector (7 downto 0);  -- Valores de entrada del acumulador
									signal REN2 : in std_logic_vector (7 downto 0);   -- Valores de entrada de los switches
									signal flag : out std_logic_vector (2 downto 0);  -- Banderas de estado
			                  signal Am   : out std_logic_vector (7 downto 0)); -- Valor a retornar
				
				-- NOT				
									
				procedure OPNOT (signal REN1 : in std_logic_vector (7 downto 0);    -- Valores de entrada del acumulador
										signal flag : out std_logic_vector (2 downto 0);  -- Banderas de estado
										signal Am   : out std_logic_vector (7 downto 0)); -- Valor a retornar
									
				-- OR
				
				procedure LOR (signal REN1 : in std_logic_vector (7 downto 0);    -- Valores de entrada del acumulador
									signal REN2 : in std_logic_vector (7 downto 0);    -- Valores de entrada de los switches
									signal flag : out std_logic_vector (2 downto 0);   -- Banderas de estado
			                  signal A    : out std_logic_vector (7 downto 0));  -- Valor a retornar
					
				-- XOR
							
				procedure LXOR (signal REN1 : in std_logic_vector (7 downto 0);   -- Valores de entrada del acumulador
									signal REN2 : in std_logic_vector (7 downto 0);    -- Valores de entrada de los switches
									signal flag : out std_logic_vector (2 downto 0);   -- Banderas de estado
			                  signal A    : out std_logic_vector (7 downto 0));  -- Valor a retornar
				
				-- AND
				procedure LAND (signal REN1 : in std_logic_vector (7 downto 0);   -- Valores de entrada del acumulador
									signal REN2 : in std_logic_vector (7 downto 0);    -- Valores de entrada de los switches
									signal flag : out std_logic_vector (2 downto 0);   -- Banderas de estado
			                  signal A    : out std_logic_vector (7 downto 0));  -- Valor a retornar
									
				-- NAND
				procedure LNAND (signal REN1 : in std_logic_vector (7 downto 0);  -- Valores de entrada del acumulador
									signal REN2 : in std_logic_vector (7 downto 0);    -- Valores de entrada de los switches
									signal flag : out std_logic_vector (2 downto 0);   -- Banderas de estado
			                  signal A    : out std_logic_vector (7 downto 0));  -- Valor a retornar
				
				-- NOR
				procedure LNOR (signal REN1 : in std_logic_vector (7 downto 0);   -- Valores de entrada del acumulador
									signal REN2 : in std_logic_vector (7 downto 0);    -- Valores de entrada de los switches
									signal flag : out std_logic_vector (2 downto 0);   -- Banderas de estado
			                  signal A    : out std_logic_vector (7 downto 0));  -- Valor a retornar
									
				-- XNOR
				procedure LXNOR (signal REN1 : in std_logic_vector (7 downto 0);  -- Valores de entrada del acumulador
									signal REN2 : in std_logic_vector (7 downto 0);    -- Valores de entrada de los switches
									signal flag : out std_logic_vector (2 downto 0);   -- Banderas de estado
			                  signal A    : out std_logic_vector (7 downto 0));  -- Valor a retornar
									
				-- INC
				procedure INC (signal REN1 : in std_logic_vector (7 downto 0);    -- Valores de entrada del acumulador
									signal flag : out std_logic_vector (2 downto 0);    -- Banderas de estado
			                  signal Am    : out std_logic_vector (7 downto 0));  -- Valor a retornar
									
				-- DEC
				procedure DEC (signal REN1 : in std_logic_vector (7 downto 0);    -- Valores de entrada del acumulador
									signal flag : out std_logic_vector (2 downto 0);   -- Banderas de estado
			                  signal Am    : out std_logic_vector (7 downto 0)); -- Valor a retornar
									
				-- SET
				procedure SET (signal REN1 : in std_logic_vector (7 downto 0);    -- Valores de entrada del acumulador
									signal flag : out std_logic_vector (2 downto 0);   -- Banderas de estado
			                  signal Am    : out std_logic_vector (7 downto 0)); -- Valor a retornar
									
				-- SLL
				procedure LSLL (signal REN1 : in std_logic_vector (15 downto 0);    -- Valores de entrada del acumulador
									signal flag : out std_logic_vector (2 downto 0);    -- Banderas de estado
			                  signal Am    : out std_logic_vector (15 downto 0));  -- Valor a retornar
				
				-- SLL
				procedure LSRL (signal REN1 : in std_logic_vector (15 downto 0);    -- Valores de entrada del acumulador
									signal flag : out std_logic_vector (2 downto 0);    -- Banderas de estado
			                  signal Am    : out std_logic_vector (15 downto 0));  -- Valor a retornar
				
			      	
			end package;
			
			
			package body ALU_UC is
			 		    
					--	Inicio de los procedimientos
					
				procedure ADD (signal REN1 : in std_logic_vector (7 downto 0);			-- Procedimiento de suma
									signal REN2 : in std_logic_vector (7 downto 0);
									signal flag : out std_logic_vector (2 downto 0);
			                  signal A    : out std_logic_vector (7 downto 0)) is
									
									begin
									
									aux(7 downto 0) <= ( REN1 + REN2 );   -- Se realiza la suma entre los dos valores
									A <= aux (7 downto 0);   																	
									 if(aux = zero) then      
		   							 flag(0) <= '1';        -- Si la operacion tuvo 0 que Z tenga 1
								    else
					    				 flag(0) <= '0';
     								 end if;
											
								    if(aux > full) then      
		   							 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
                            else
										 flag(1) <= '0';       
    			  					 end if;
											
								    if(aux < zero) then      
		   							 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
					             else
										 flag(2) <= '0';				
					   			 end if;			
									
				end ADD;
				
				procedure SUB (signal REN1 : in std_logic_vector (7 downto 0);							-- Procedimiento para resta
									signal REN2 : in std_logic_vector (7 downto 0);
									signal flag : out std_logic_vector (2 downto 0);
			                  signal A    : out std_logic_vector (7 downto 0)) is
									
									begin
									
									aux(7 downto 0) <= (REN1 - REN2);	 -- Se resta REN1 con REN2
									A <= aux(7 downto 0);		-- Retornamos el resultado de la operación
									
									 if(aux = zero) then      
		   						    flag(0) <= '1';        -- Si la operacion tuvo 0 que Z tenga 1
								    else
					    				 flag(0) <= '0';
     								 end if;
											
								    if(aux > full) then      
		   							 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
                            else
										 flag(1) <= '0';       
    			  					 end if;
											
								    if(aux < zero) then      
		   							 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
					             else
										 flag(2) <= '0';				
					   			 end if;
				
				end SUB;
				
				procedure MUL (signal REN1 : in std_logic_vector (7 downto 0);				-- Procedimiento para multiplicacion
									signal REN2 : in std_logic_vector (7 downto 0);
									signal flag : out std_logic_vector (2 downto 0);
			                  signal Am   : out std_logic_vector (15 downto 0)) is
									
									begin
									
									aux <= std_logic_vector( signed(REN1) * signed(REN2) ); -- Se realiza la operación
									Am <= aux;    					-- Retornamos el resultado de la operación
									
									 if(aux = zero) then      
		   						    flag(0) <= '1';        -- Si la operacion tuvo 0 que Z tenga 1
								    else
					    				 flag(0) <= '0';
     								 end if;
											
								    if(aux > full) then      
		   							 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
                            else
										 flag(1) <= '0';       
    			  					 end if;
											
								    if(aux < zero) then      
		   							 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
					             else
										 flag(2) <= '0';				
					   			 end if;
				
				end MUL;
				
				procedure DIVI (signal REN1 : in std_logic_vector (7 downto 0);				-- Procedimiento para división
									signal REN2 : in std_logic_vector (7 downto 0);
									signal flag : out std_logic_vector (2 downto 0);
			                  signal Am   : out std_logic_vector (7 downto 0)) is
									
									begin
									
									 aux(7 downto 0) <= std_logic_vector( signed(REN1) / signed(REN2) ); -- Se realiza la operación
									 
									 Am <= aux(7 downto 0);    -- Retornamos el resultado de la operación
									
									 if(aux = zero) then      
		   						    flag(0) <= '1';        -- Si la operacion tuvo 0 que Z tenga 1
								    else
					    				 flag(0) <= '0';
     								 end if;
											
								    if(aux > full) then      
		   							 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
                            else
										 flag(1) <= '0';       
    			  					 end if;
											
								    if(aux < zero) then      
		   							 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
					             else
										 flag(2) <= '0';				
					   			 end if;
				
				end DIVI;
				
				procedure OPNOT (signal REN1 : in std_logic_vector (7 downto 0);						-- Procedimiento para NOT
										signal flag : out std_logic_vector (2 downto 0);
										signal Am   : out std_logic_vector (7 downto 0)) is 
										
										begin
										aux (7 downto 0) <= Not REN1; -- Se realiza la operación
										
										Am <= aux(7 downto 0);     -- Retornamos el resultado de la operación
										
										if(aux = zero) then      
		   						    flag(0) <= '1';       	 	-- Si la operacion tuvo 0 que Z tenga 1
										else
											 flag(0) <= '0';
										end if;
												
										if(aux > full) then      
											 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
										else
											 flag(1) <= '0';       
										end if;
												
										if(aux < zero) then      
											 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
										else
											 flag(2) <= '0';				
										end if;
				end OPNOT;
				
				procedure LOR (signal REN1 : in std_logic_vector (7 downto 0);							-- Procedimiento para OR
									signal REN2 : in std_logic_vector (7 downto 0);
									signal flag : out std_logic_vector (2 downto 0);
			                  signal A    : out std_logic_vector (7 downto 0)) is
									
									begin
				
							       aux(7 downto 0) <= (REN1 OR REN2); -- Se realiza la operación
									 A <= aux(7 downto 0);     -- Retornamos el resultado de la operación
									 
									 if(aux = zero) then      
		   						    flag(0) <= '1';        -- Si la operacion tuvo 0 que Z tenga 1
								    else
					    				 flag(0) <= '0';
     								 end if;
											
								    if(aux > full) then      
		   							 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
                            else
										 flag(1) <= '0';       
    			  					 end if;
											
								    if(aux < zero) then      
		   							 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
					             else
										 flag(2) <= '0';				
					   			 end if;
				
				
				end LOR;

				procedure LXOR (signal REN1 : in std_logic_vector (7 downto 0);							-- Procedimiento para XOR
									signal REN2 : in std_logic_vector (7 downto 0);
									signal flag : out std_logic_vector (2 downto 0);
			                  signal A    : out std_logic_vector (7 downto 0)) is
									
									begin
				
							       aux(7 downto 0) <= (REN1 XOR REN2); -- Se realiza la operación
									 A <= aux(7 downto 0);     -- Retornamos el resultado de la operación
									 
									 if(aux = zero) then      
		   						    flag(0) <= '1';        -- Si la operacion tuvo 0 que Z tenga 1
								    else
					    				 flag(0) <= '0';
     								 end if;
											
								    if(aux > full) then      
		   							 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
                            else
										 flag(1) <= '0';       
    			  					 end if;
											
								    if(aux < zero) then      
		   							 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
					             else
										 flag(2) <= '0';				
					   			 end if;
				
				
				end LXOR;
				
				procedure LAND (signal REN1 : in std_logic_vector (7 downto 0);							-- Procedimiento para NAND
									signal REN2 : in std_logic_vector (7 downto 0);
									signal flag : out std_logic_vector (2 downto 0);
			                  signal A    : out std_logic_vector (7 downto 0)) is
									
									begin
				
							       aux(7 downto 0) <= (REN1 AND REN2); -- Se realiza la operación
									 A <= aux(7 downto 0);     -- Retornamos el resultado de la operación
									 
									 if(aux = zero) then      
		   						    flag(0) <= '1';        -- Si la operacion tuvo 0 que Z tenga 1
								    else
					    				 flag(0) <= '0';
     								 end if;
											
								    if(aux > full) then      
		   							 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
                            else
										 flag(1) <= '0';       
    			  					 end if;
											
								    if(aux < zero) then      
		   							 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
					             else
										 flag(2) <= '0';				
					   			 end if;
				
				
				end LAND;
				
				
				procedure LNAND (signal REN1 : in std_logic_vector (7 downto 0);							-- Procedimiento para NAND
									signal REN2 : in std_logic_vector (7 downto 0);
									signal flag : out std_logic_vector (2 downto 0);
			                  signal A    : out std_logic_vector (7 downto 0)) is
									
									begin
				
							       aux(7 downto 0) <= (REN1 NAND REN2); -- Se realiza la operación
									 A <= aux(7 downto 0);     -- Retornamos el resultado de la operación
									 
									 if(aux = zero) then      
		   						    flag(0) <= '1';        -- Si la operacion tuvo 0 que Z tenga 1
								    else
					    				 flag(0) <= '0';
     								 end if;
											
								    if(aux > full) then      
		   							 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
                            else
										 flag(1) <= '0';       
    			  					 end if;
											
								    if(aux < zero) then      
		   							 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
					             else
										 flag(2) <= '0';				
					   			 end if;
				
				
				end LNAND;
				
				
				procedure LNOR (signal REN1 : in std_logic_vector (7 downto 0);							-- Procedimiento para NOR
									signal REN2 : in std_logic_vector (7 downto 0);
									signal flag : out std_logic_vector (2 downto 0);
			                  signal A    : out std_logic_vector (7 downto 0)) is
									
									begin
				
							       aux(7 downto 0) <= (REN1 NOR REN2); -- Se realiza la operación
									 A <= aux(7 downto 0);     -- Retornamos el resultado de la operación
									 
									 if(aux = zero) then      
		   						    flag(0) <= '1';        -- Si la operacion tuvo 0 que Z tenga 1
								    else
					    				 flag(0) <= '0';
     								 end if;
											
								    if(aux > full) then      
		   							 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
                            else
										 flag(1) <= '0';       
    			  					 end if;
											
								    if(aux < zero) then      
		   							 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
					             else
										 flag(2) <= '0';				
					   			 end if;
				
				
				end LNOR;
				
				
				procedure LXNOR (signal REN1 : in std_logic_vector (7 downto 0);							-- Procedimiento para LXNOR
									signal REN2 : in std_logic_vector (7 downto 0);
									signal flag : out std_logic_vector (2 downto 0);
			                  signal A    : out std_logic_vector (7 downto 0)) is
									
									begin
				
							       aux(7 downto 0) <= (REN1 XNOR REN2); -- Se realiza la operación
									 A <= aux(7 downto 0);     -- Retornamos el resultado de la operación
									 
									 if(aux = zero) then      
		   						    flag(0) <= '1';        -- Si la operacion tuvo 0 que Z tenga 1
								    else
					    				 flag(0) <= '0';
     								 end if;
											
								    if(aux > full) then      
		   							 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
                            else
										 flag(1) <= '0';       
    			  					 end if;
											
								    if(aux < zero) then      
		   							 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
					             else
										 flag(2) <= '0';				
					   			 end if;
				
				
				end LXNOR;
				
				procedure INC (signal REN1 : in std_logic_vector (7 downto 0);						-- Procedimiento para INC
										signal flag : out std_logic_vector (2 downto 0);
										signal Am   : out std_logic_vector (7 downto 0)) is 
										
										begin
										aux (7 downto 0) <= REN1+1; -- Se realiza la operación
										
										Am <= aux(7 downto 0);     -- Retornamos el resultado de la operación
										
										if(aux = zero) then      
		   						    flag(0) <= '1';       	 	-- Si la operacion tuvo 0 que Z tenga 1
										else
											 flag(0) <= '0';
										end if;
												
										if(aux > full) then      
											 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
										else
											 flag(1) <= '0';       
										end if;
												
										if(aux < zero) then      
											 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
										else
											 flag(2) <= '0';				
										end if;
				end INC;
				
				
				procedure DEC (signal REN1 : in std_logic_vector (7 downto 0);						-- Procedimiento para DEC
										signal flag : out std_logic_vector (2 downto 0);
										signal Am   : out std_logic_vector (7 downto 0)) is 
										
										begin
										aux (7 downto 0) <= REN1 - 1; -- Se realiza la operación
										
										Am <= aux(7 downto 0);     -- Retornamos el resultado de la operación
										
										if(aux = zero) then      
		   						    flag(0) <= '1';       	 	-- Si la operacion tuvo 0 que Z tenga 1
										else
											 flag(0) <= '0';
										end if;
												
										if(aux > full) then      
											 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
										else
											 flag(1) <= '0';       
										end if;
												
										if(aux < zero) then      
											 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
										else
											 flag(2) <= '0';				
										end if;
				end DEC;
				
				procedure SET (signal REN1 : in std_logic_vector (15 downto 0);						-- Procedimiento para SET
										signal flag : out std_logic_vector (2 downto 0);
										signal Am   : out std_logic_vector (15 downto 0)) is 
										
										begin
										aux <= "1111111111111111"; -- Se realiza la operación
										
										Am <= aux;     -- Retornamos el resultado de la operación
										
										if(aux = zero) then      
		   						    flag(0) <= '1';       	 	-- Si la operacion tuvo 0 que Z tenga 1
										else
											 flag(0) <= '0';
										end if;
												
										if(aux > full) then      
											 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
										else
											 flag(1) <= '0';       
										end if;
												
										if(aux < zero) then      
											 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
										else
											 flag(2) <= '0';				
										end if;
									      
				end SET;
				
				
				procedure LSLL (signal REN1 : in std_logic_vector (15 downto 0);						-- Procedimiento para LSLL
										signal flag : out std_logic_vector (2 downto 0);
										signal Am   : out std_logic_vector (15 downto 0)) is 
										
										begin
										
										aux <= REN1(13 downto 0)& "00" ; -- Se hace el recorrido en la posicion 2
										Am <= aux;     -- Retornamos el resultado de la operación
										
										if(aux = zero) then      
		   						    flag(0) <= '1';       	 	-- Si la operacion tuvo 0 que Z tenga 1
										else
											 flag(0) <= '0';
										end if;
												
										if(aux > full) then      
											 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
										else
											 flag(1) <= '0';       
										end if;
												
										if(aux < zero) then      
											 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
										else
											 flag(2) <= '0';				
										end if;
									      
				end LSLL;
				
				procedure LSRL (signal REN1 : in std_logic_vector (15 downto 0);						-- Procedimiento para LSRL 
										signal flag : out std_logic_vector (2 downto 0);
										signal Am   : out std_logic_vector (15 downto 0)) is 
										
										begin
										
										aux <= "00"&REN1(15 downto 2) ; -- Se hace el recorrido en la posicion 2
										Am <= aux;     -- Retornamos el resultado de la operación
										
										if(aux = zero) then      
		   						    flag(0) <= '1';       	 	-- Si la operacion tuvo 0 que Z tenga 1
										else
											 flag(0) <= '0';
										end if;
												
										if(aux > full) then      
											 flag(1) <= '1';        -- Si la operacion excedio la capacidad del registro, que V tenga 1													
										else
											 flag(1) <= '0';       
										end if;
												
										if(aux < zero) then      
											 flag(2) <= '1';        -- Si la operacion resulto negativa que N tenga 1
										else
											 flag(2) <= '0';				
										end if;
									      
				end LSRL;
				
		   end ALU_UC;

			