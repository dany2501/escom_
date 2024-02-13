LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

PACKAGE pmodDigilent2digits IS

    TYPE state IS (S1, S2);

    PROCEDURE displayConv (
        SIGNAL switch : IN STD_LOGIC_VECTOR (3 DOWNTO 0);
        SIGNAL display : OUT STD_LOGIC_VECTOR (6 DOWNTO 0));

    PROCEDURE transition (
        SIGNAL actualState : INOUT state;
        SIGNAL clockSig : IN STD_LOGIC;
        SIGNAL rst : IN STD_LOGIC);

    PROCEDURE outputs (
        SIGNAL actualState : IN state;
        SIGNAL countSign : OUT STD_LOGIC);

    PROCEDURE assignDisplay (
        SIGNAL MUX : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
        SIGNAL seg_out : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL countSign : IN STD_LOGIC);

    PROCEDURE tavelZero (
        SIGNAL AN : OUT STD_LOGIC;
        SIGNAL countSign : IN STD_LOGIC);

END pmodDigilent2digits;

PACKAGE BODY pmodDigilent2digits IS
    PROCEDURE displayConv (
        SIGNAL switch : IN STD_LOGIC_VECTOR (3 DOWNTO 0);
        SIGNAL display : OUT STD_LOGIC_VECTOR (6 DOWNTO 0)) IS

    BEGIN
        CASE switch IS
            WHEN "0000" => display <= "1111110";
            WHEN "0001" => display <= "0110000";
            WHEN "0010" => display <= "1101101";
            WHEN "0011" => display <= "1111001";
            WHEN "0100" => display <= "0110011";
            WHEN "0101" => display <= "1011011";
            WHEN "0110" => display <= "1011111";
            WHEN "0111" => display <= "1110001";
            WHEN "1000" => display <= "1111111";
            WHEN "1001" => display <= "1111011";
            WHEN "1010" => display <= "1110111";
            WHEN "1011" => display <= "0011111";
            WHEN "1100" => display <= "1001110";
            WHEN "1101" => display <= "0111101";
            WHEN "1110" => display <= "1001111";
            WHEN "1111" => display <= "1000111";
            WHEN OTHERS => display <= "0000000";
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
                WHEN OTHERS => actualState <= S1;
            END CASE;
        END IF;
    END transition;

    PROCEDURE outputs(
        SIGNAL actualState : IN state;
        SIGNAL countSign : OUT STD_LOGIC) IS
    BEGIN
        CASE actualState IS
            WHEN S1 => countSign <= '0';
            WHEN S2 => countSign <= '1';
            WHEN OTHERS => countSign <= '0';
        END CASE;
    END outputs;

    PROCEDURE assignDisplay(
        SIGNAL MUX : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
        SIGNAL seg_out : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL countSign : IN STD_LOGIC) IS
    BEGIN
        WITH countSign SELECT
            MUX <= seg_out(3 DOWNTO 0) WHEN '0',
            seg_out(7 DOWNTO 4) WHEN OTHERS;
    END assignDisplay;

    PROCEDURE tavelZero(
        SIGNAL AN : OUT STD_LOGIC;
        SIGNAL countSign : IN STD_LOGIC) IS
    BEGIN
        WITH countSign SELECT
            AN <= '0' WHEN '0',
            '1' WHEN OTHERS;
    END tavelZero;

END pmodDigilent2digits;