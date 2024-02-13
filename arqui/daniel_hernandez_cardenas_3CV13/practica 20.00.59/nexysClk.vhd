LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.ALL;

PACKAGE nexysClk IS
    PROCEDURE sleepClk (
        SIGNAL clk : IN STD_LOGIC;
        SIGNAL rst : IN STD_LOGIC;
        milliseconds : IN INTEGER;
        frequencyDiv : IN INTEGER;
        SIGNAL count : INOUT INTEGER;
        SIGNAL clkOut : INOUT STD_LOGIC);
END nexysClk;

PACKAGE BODY nexysClk IS

    PROCEDURE sleepClk (
        SIGNAL clk : IN STD_LOGIC;
        SIGNAL rst : IN STD_LOGIC;
        milliseconds : IN INTEGER;
        frequencyDiv : IN INTEGER;
        SIGNAL count : INOUT INTEGER;
        SIGNAL clkOut : INOUT STD_LOGIC) IS
    BEGIN
        IF (rst = '0') THEN
            count <= 1;
            clkOut <= '0';
        ELSIF rising_edge(clk) THEN
            count <= count + 1;
            IF (count = frequencyDiv * milliseconds) THEN
                clkOut <= NOT clkOut;
                count <= 1;
            END IF;
        END IF;
    END sleepClk;

END nexysClk;