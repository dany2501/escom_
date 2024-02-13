LIBRARY IEEE;

USE IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.ALL;
USE work.nexysSwitchToDisplay;
USE work.pmodDigilent2digits;
USE work.nexysClk.ALL;
USE work.nexysRAM.ALL;
USE work.nexysALU.ALL;

ENTITY SwitchToDisplay IS
    PORT (
        clk : IN STD_LOGIC;
        rst : IN STD_LOGIC;
        exe : IN STD_LOGIC;
        ent_datos : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        ent_inst : IN STD_LOGIC_VECTOR(4 DOWNTO 0);
        flag : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
        bus_datos : INOUT STD_LOGIC_VECTOR(7 DOWNTO 0);
        bus_ctrl : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
        seg_out : OUT STD_LOGIC_VECTOR(21 DOWNTO 0);
        AN : OUT STD_LOGIC_VECTOR(9 DOWNTO 0)
    );
END SwitchToDisplay;

ARCHITECTURE sim OF SwitchToDisplay IS
    SIGNAL AS : nexysSwitchToDisplay.state := nexysSwitchToDisplay.S1;
    SIGNAL AS_PMOD : pmodDigilent2digits.state := pmodDigilent2digits.S1;
    SIGNAL MUX : STD_LOGIC_VECTOR(11 DOWNTO 0);
    SIGNAL AUXDISPLAY : STD_LOGIC_VECTOR (47 DOWNTO 0);
    SIGNAL countSign : STD_LOGIC_VECTOR(2 DOWNTO 0);
    SIGNAL countSign_pmod : STD_LOGIC;
    SIGNAL count : INTEGER := 1;
    SIGNAL clockSig : STD_LOGIC := '0';
    SIGNAL human_clockSig : STD_LOGIC := '0';

    SIGNAL bus_dir : STD_LOGIC_VECTOR(7 DOWNTO 0);
    SIGNAL AX : STD_LOGIC_VECTOR (15 DOWNTO 0) := "0000000000000000"; -- Reg. Acumulador
    SIGNAL PC : unsigned(7 DOWNTO 0) := "00000000";
    SIGNAL IX : STD_LOGIC_VECTOR (7 DOWNTO 0) := "00000000"; -- Reg. Indice
    SIGNAL inst : STD_LOGIC_VECTOR(3 DOWNTO 0) := "0000"; -- zero
    SIGNAL aux : STD_LOGIC_VECTOR(7 DOWNTO 0) := "00000000"; -- auxiliar
BEGIN
    sleepClk(clk, rst, 1, 10000, count, clockSig);
    sleepClk(clk, rst, 100, 1000, count, human_clockSig);
    AUXDISPLAY <= STD_LOGIC_VECTOR(PC) & IX & AX & "000" & ent_inst & bus_dir;

    nexysSwitchToDisplay.assignDisplay(MUX(3 DOWNTO 0), AUXDISPLAY(31 DOWNTO 0), countSign);
    nexysSwitchToDisplay.displayConv(MUX(3 DOWNTO 0), seg_out(7 DOWNTO 0));
    nexysSwitchToDisplay.tavelZero(AN(7 DOWNTO 0), countSign);
    nexysSwitchToDisplay.transition(AS, clockSig, rst);
    nexysSwitchToDisplay.outputs(AS, countSign);

    pmodDigilent2digits.assignDisplay(MUX(7 DOWNTO 4), AUXDISPLAY(39 DOWNTO 32), countSign_pmod);
    pmodDigilent2digits.displayConv(MUX(7 DOWNTO 4), seg_out(14 DOWNTO 8));
    pmodDigilent2digits.tavelZero(AN(8), countSign_pmod);

    pmodDigilent2digits.assignDisplay(MUX(11 DOWNTO 8), AUXDISPLAY(47 DOWNTO 40), countSign_pmod);
    pmodDigilent2digits.displayConv(MUX(11 DOWNTO 8), seg_out(21 DOWNTO 15));
    pmodDigilent2digits.tavelZero(AN(9), countSign_pmod);

    pmodDigilent2digits.transition(AS_PMOD, clockSig, rst);
    pmodDigilent2digits.outputs(AS_PMOD, countSign_pmod);

    UC : PROCESS (rst)
    BEGIN
        IF (rst = '0') THEN
            PC <= "00000000";
            AX <= "0000000000000000";
            IX <= "00000000";
        END IF;

        CASE ent_inst IS --	Set de instrucciones
            WHEN "00000" => -- CLA
                AX <= "0000000000000000";
            WHEN "00001" => -- MOVX
                AX(7 DOWNTO 0) <= ent_datos;
            WHEN "00010" => -- MOVIX
                MOVIX(human_clockSig, IX, AX, ent_datos, bus_datos, bus_ctrl, bus_dir);
            WHEN "00011" => -- MOVIA
                MOVIA(human_clockSig, IX, AX, ent_datos, bus_datos, bus_ctrl, bus_dir);
            WHEN "00100" => -- ADD
                ADD(AX(7 DOWNTO 0), ent_datos, flag, AX(7 DOWNTO 0));
            WHEN "00101" => -- SUB
                SUB(AX(7 DOWNTO 0), ent_datos, flag, AX(7 DOWNTO 0));
            WHEN "00110" => -- LOR
                LOR(AX(7 DOWNTO 0), ent_datos, flag, AX(7 DOWNTO 0));
            WHEN "00111" => -- LAND
                LAND(AX(7 DOWNTO 0), ent_datos, flag, AX(7 DOWNTO 0));
            WHEN "01000" => -- LNOTAX
                LNOT(AX(7 DOWNTO 0), flag, AX(7 DOWNTO 0));
            WHEN "01001" => -- LNOTIX
                LNOT(ent_datos, flag, AX(7 DOWNTO 0));
            WHEN "01010" => -- LNOR
                LNOR(AX(7 DOWNTO 0), ent_datos, flag, AX(7 DOWNTO 0));
            WHEN "01011" => -- LNAND
                LNAND(AX(7 DOWNTO 0), ent_datos, flag, AX(7 DOWNTO 0));
            WHEN "01110" => -- LXOR
                LXOR(AX(7 DOWNTO 0), ent_datos, flag, AX(7 DOWNTO 0));
            WHEN "01111" => -- LXNOR
                LXNOR(AX(7 DOWNTO 0), ent_datos, flag, AX(7 DOWNTO 0));
            WHEN "10000" => -- SLRAX
                SLRAX(AX(7 DOWNTO 0), flag, AX(7 DOWNTO 0));
            WHEN "10001" => -- SLLAX
                SLLAX(AX(7 DOWNTO 0), flag, AX(7 DOWNTO 0));
            WHEN "10010" => -- SLRIX
                SLRAX(ent_datos, flag, AX(7 DOWNTO 0));
            WHEN "10011" => -- SLLIX
                SLLAX(ent_datos, flag, AX(7 DOWNTO 0));
            WHEN "10100" => -- MUL
                MUL(AX(7 DOWNTO 0), ent_datos, flag, AX);
            WHEN OTHERS =>
                PC <= "00000000";
                AX <= "0000000000000000";
                IX <= "00000000";
        END CASE;

    END PROCESS;

END sim;