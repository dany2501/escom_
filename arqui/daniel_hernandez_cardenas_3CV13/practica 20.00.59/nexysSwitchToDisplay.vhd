LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

PACKAGE nexysSwitchToDisplay IS

    TYPE state IS (S1, S2, S3, S4, S5, S6, S7, S8);

    PROCEDURE displayConv (
        SIGNAL switch : IN STD_LOGIC_VECTOR (3 DOWNTO 0);
        SIGNAL display : OUT STD_LOGIC_VECTOR (7 DOWNTO 0));

    PROCEDURE transition (
        SIGNAL actualState : INOUT state;
        SIGNAL clockSig : IN STD_LOGIC;
        SIGNAL rst : IN STD_LOGIC);

    PROCEDURE outputs (
        SIGNAL actualState : IN state;
        SIGNAL countSign : OUT STD_LOGIC_VECTOR(2 DOWNTO 0));

    PROCEDURE assignDisplay (
        SIGNAL MUX : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
        SIGNAL seg_out : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
        SIGNAL countSign : IN STD_LOGIC_VECTOR(2 DOWNTO 0));

    PROCEDURE tavelZero (
        SIGNAL AN : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL countSign : IN STD_LOGIC_VECTOR(2 DOWNTO 0));

END nexysSwitchToDisplay;

PACKAGE BODY nexysSwitchToDisplay IS
    PROCEDURE displayConv (
        SIGNAL switch : IN STD_LOGIC_VECTOR (3 DOWNTO 0);
        SIGNAL display : OUT STD_LOGIC_VECTOR (7 DOWNTO 0)) IS

    BEGIN
        CASE switch IS
            WHEN "0000" => display <= "00000011";
            WHEN "0001" => display <= "10011111";
            WHEN "0010" => display <= "00100101";
            WHEN "0011" => display <= "00001101";
            WHEN "0100" => display <= "10011001";
            WHEN "0101" => display <= "01001001";
            WHEN "0110" => display <= "01000001";
            WHEN "0111" => display <= "00011101";
            WHEN "1000" => display <= "00000001";
            WHEN "1001" => display <= "00001001";
            WHEN "1010" => display <= "00010001";
            WHEN "1011" => display <= "11000001";
            WHEN "1100" => display <= "01100011";
            WHEN "1101" => display <= "10000101";
            WHEN "1110" => display <= "01100001";
            WHEN "1111" => display <= "01110001";
            WHEN OTHERS => display <= "11111111";
        END CASE;
    END displayConv;

    PROCEDURE transition (
        SIGNAL actualState : INOUT state;
        SIGNAL clockSig : IN STD_LOGIC;
        SIGNAL rst : IN STD_LOGIC) IS
    BEGIN
        IF (rst = '0') THEN
            actualState <= S1;
        ELSIF (clockSig = '1') THEN
            CASE actualState IS
                WHEN S1 => actualState <= S2;
                WHEN S2 => actualState <= S3;
                WHEN S3 => actualState <= S4;
                WHEN S4 => actualState <= S5;
                WHEN S5 => actualState <= S6;
                WHEN S6 => actualState <= S7;
                WHEN S7 => actualState <= S8;
                WHEN S8 => actualState <= S1;
                WHEN OTHERS => actualState <= S1;
            END CASE;
        END IF;
    END transition;

    PROCEDURE outputs(
        SIGNAL actualState : IN state;
        SIGNAL countSign : OUT STD_LOGIC_VECTOR(2 DOWNTO 0)) IS
    BEGIN
        CASE actualState IS
            WHEN S1 => countSign <= "000";
            WHEN S2 => countSign <= "001";
            WHEN S3 => countSign <= "010";
            WHEN S4 => countSign <= "011";
            WHEN S5 => countSign <= "100";
            WHEN S6 => countSign <= "101";
            WHEN S7 => countSign <= "110";
            WHEN S8 => countSign <= "111";
            WHEN OTHERS => countSign <= "000";
        END CASE;
    END outputs;

    PROCEDURE assignDisplay(
        SIGNAL MUX : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
        SIGNAL seg_out : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
        SIGNAL countSign : IN STD_LOGIC_VECTOR(2 DOWNTO 0)) IS
    BEGIN
        WITH countSign SELECT
            MUX <= seg_out(3 DOWNTO 0) WHEN "000",
            seg_out(7 DOWNTO 4) WHEN "001",
            seg_out(11 DOWNTO 8) WHEN "010",
            seg_out(15 DOWNTO 12) WHEN "011",
            seg_out(19 DOWNTO 16) WHEN "100",
            seg_out(23 DOWNTO 20) WHEN "101",
            seg_out(27 DOWNTO 24) WHEN "110",
            seg_out(31 DOWNTO 28) WHEN OTHERS;
    END assignDisplay;

    PROCEDURE tavelZero(
        SIGNAL AN : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL countSign : IN STD_LOGIC_VECTOR(2 DOWNTO 0)) IS
    BEGIN
        WITH countSign SELECT
            AN <= "11111110" WHEN "000",
            "11111101" WHEN "001",
            "11111011" WHEN "010",
            "11110111" WHEN "011",
            "11101111" WHEN "100",
            "11011111" WHEN "101",
            "10111111" WHEN "110",
            "01111111" WHEN OTHERS;
    END tavelZero;

END nexysSwitchToDisplay;