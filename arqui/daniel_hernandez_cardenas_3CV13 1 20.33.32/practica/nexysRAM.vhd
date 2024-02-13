LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

PACKAGE nexysRAM IS

    PROCEDURE MOVIX (
        SIGNAL clk : IN STD_LOGIC;
        SIGNAL IX : INOUT STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL AX : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);
        SIGNAL ent_datos : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL bus_datos : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL bus_ctrl : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
        SIGNAL bus_dir : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
    );

    PROCEDURE MOVIA (
        SIGNAL clk : IN STD_LOGIC;
        SIGNAL IX : INOUT STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL AX : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
        SIGNAL ent_datos : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL bus_datos : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL bus_ctrl : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
        SIGNAL bus_dir : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
    );
END nexysRAM;

PACKAGE BODY nexysRAM IS

    PROCEDURE MOVIX(
        SIGNAL clk : IN STD_LOGIC;
        SIGNAL IX : INOUT STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL AX : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);
        SIGNAL ent_datos : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL bus_datos : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL bus_ctrl : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
        SIGNAL bus_dir : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)) IS
    BEGIN
        IX <= ent_datos;
        bus_ctrl (0) <= '0';
        bus_ctrl (1) <= '0';
        bus_ctrl (2) <= '0';
        bus_ctrl (3) <= '0';
        bus_ctrl (4) <= '0';
        bus_ctrl (5) <= '0';
        bus_ctrl (6) <= '1';
        bus_ctrl (7) <= '0';
        bus_ctrl (8) <= '1';
        bus_ctrl (9) <= clk;
        bus_ctrl (10) <= '1';
        bus_ctrl (11) <= '1';
        bus_dir (7) <= '1';
        bus_dir <= IX;
        AX <= STD_LOGIC_VECTOR("00000000" & bus_datos);
    END MOVIX;

    PROCEDURE MOVIA(
        SIGNAL clk : IN STD_LOGIC;
        SIGNAL IX : INOUT STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL AX : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
        SIGNAL ent_datos : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL bus_datos : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
        SIGNAL bus_ctrl : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
        SIGNAL bus_dir : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)) IS
    BEGIN
        IX <= ent_datos;
        bus_ctrl (0) <= '0';
        bus_ctrl (1) <= '0';
        bus_ctrl (2) <= '0';
        bus_ctrl (3) <= '0';
        bus_ctrl (4) <= '0';
        bus_ctrl (5) <= '0';
        bus_ctrl (6) <= '1';
        bus_ctrl (7) <= '0';
        bus_ctrl (8) <= '1';
        bus_ctrl (9) <= clk;
        bus_ctrl (10) <= '0';
        bus_ctrl (11) <= '1';
        bus_dir (7) <= '1';
        bus_dir <= IX;
        bus_datos <= AX (7 DOWNTO 0);
    END MOVIA;

END nexysRAM;