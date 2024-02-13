LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_signed.ALL;
USE ieee.numeric_std.ALL;

PACKAGE nexysALU IS

    CONSTANT zero : STD_LOGIC_VECTOR(7 DOWNTO 0) := "00000000";
    CONSTANT full : STD_LOGIC_VECTOR(7 DOWNTO 0) := "00001111";

    PROCEDURE ADD (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)
    );

    PROCEDURE SUB (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)
    );

    PROCEDURE MUL (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL Am : OUT STD_LOGIC_VECTOR (15 DOWNTO 0));

    PROCEDURE LOR (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)
    );

    PROCEDURE LAND (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)
    );

    PROCEDURE LNOT (
        SIGNAL REN : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)
    );

    PROCEDURE LNOR (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)
    );

    PROCEDURE LNAND (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)
    );

    PROCEDURE LXOR (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)
    );

    PROCEDURE LXNOR (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)
    );

    PROCEDURE SLRAX (
        SIGNAL REN : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)
    );

    PROCEDURE SLLAX (
        SIGNAL REN : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)
    );
END PACKAGE;
PACKAGE BODY nexysALU IS

    PROCEDURE ADD (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0); -- Procedimiento de suma
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)) IS

    BEGIN

        A <= (REN1 + REN2);
        IF (A = zero) THEN
            flag(0) <= '1';
        ELSE
            flag(0) <= '0';
        END IF;

        IF (A > full) THEN
            flag(1) <= '1';
        ELSE
            flag(1) <= '0';
        END IF;

        IF (A < zero) THEN
            flag(2) <= '1';
        ELSE
            flag(2) <= '0';
        END IF;

    END ADD;

    PROCEDURE SUB (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0); -- Procedimiento para resta
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)) IS

    BEGIN

        A <= (REN1 - REN2); -- Se resta REN1 con REN2

        IF (A = zero) THEN
            flag(0) <= '1';
        ELSE
            flag(0) <= '0';
        END IF;

        IF (A > full) THEN
            flag(1) <= '1';
        ELSE
            flag(1) <= '0';
        END IF;

        IF (A < zero) THEN
            flag(2) <= '1';
        ELSE
            flag(2) <= '0';
        END IF;

    END SUB;

    PROCEDURE MUL (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0); -- Procedimiento para multiplicacion
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL Am : OUT STD_LOGIC_VECTOR (15 DOWNTO 0)) IS

    BEGIN

        Am <= STD_LOGIC_VECTOR(signed(REN1) * signed(REN2));

        IF (Am = zero) THEN
            flag(0) <= '1';
        ELSE
            flag(0) <= '0';
        END IF;

        IF (Am > full) THEN
            flag(1) <= '1';
        ELSE
            flag(1) <= '0';
        END IF;

        IF (Am < zero) THEN
            flag(2) <= '1';
        ELSE
            flag(2) <= '0';
        END IF;

    END MUL;

    PROCEDURE LOR (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0); -- Procedimiento para OR
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)) IS

    BEGIN

        A <= (REN1 OR REN2);

        IF (A = zero) THEN
            flag(0) <= '1';
        ELSE
            flag(0) <= '0';
        END IF;

        IF (A > full) THEN
            flag(1) <= '1';
        ELSE
            flag(1) <= '0';
        END IF;

        IF (A < zero) THEN
            flag(2) <= '1';
        ELSE
            flag(2) <= '0';
        END IF;
    END LOR;

    PROCEDURE LAND (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)) IS

    BEGIN

        A <= (REN1 AND REN2);

        IF (A = zero) THEN
            flag(0) <= '1';
        ELSE
            flag(0) <= '0';
        END IF;

        IF (A > full) THEN
            flag(1) <= '1';
        ELSE
            flag(1) <= '0';
        END IF;

        IF (A < zero) THEN
            flag(2) <= '1';
        ELSE
            flag(2) <= '0';
        END IF;
    END LAND;

    PROCEDURE LNOT (
        SIGNAL REN : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)
    ) IS

    BEGIN

        A <= (NOT REN);

        IF (A = zero) THEN
            flag(0) <= '1';
        ELSE
            flag(0) <= '0';
        END IF;

        IF (A > full) THEN
            flag(1) <= '1';
        ELSE
            flag(1) <= '0';
        END IF;

        IF (A < zero) THEN
            flag(2) <= '1';
        ELSE
            flag(2) <= '0';
        END IF;
    END LNOT;

    PROCEDURE LNOR (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0); -- Procedimiento para NOR
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)) IS

    BEGIN

        A <= (NOT (REN1 OR REN2));

        IF (A = zero) THEN
            flag(0) <= '1';
        ELSE
            flag(0) <= '0';
        END IF;

        IF (A > full) THEN
            flag(1) <= '1';
        ELSE
            flag(1) <= '0';
        END IF;

        IF (A < zero) THEN
            flag(2) <= '1';
        ELSE
            flag(2) <= '0';
        END IF;
    END LNOR;

    PROCEDURE LNAND (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0); -- Procedimiento para NAND
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)) IS

    BEGIN

        A <= (NOT (REN1 NAND REN2));

        IF (A = zero) THEN
            flag(0) <= '1';
        ELSE
            flag(0) <= '0';
        END IF;

        IF (A > full) THEN
            flag(1) <= '1';
        ELSE
            flag(1) <= '0';
        END IF;

        IF (A < zero) THEN
            flag(2) <= '1';
        ELSE
            flag(2) <= '0';
        END IF;
    END LNAND;

    PROCEDURE LXOR (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0); -- Procedimiento para NAND
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)) IS

    BEGIN

        A <= (NOT (REN1 XOR REN2));

        IF (A = zero) THEN
            flag(0) <= '1';
        ELSE
            flag(0) <= '0';
        END IF;

        IF (A > full) THEN
            flag(1) <= '1';
        ELSE
            flag(1) <= '0';
        END IF;

        IF (A < zero) THEN
            flag(2) <= '1';
        ELSE
            flag(2) <= '0';
        END IF;
    END LXOR;

    PROCEDURE LXNOR (
        SIGNAL REN1 : IN STD_LOGIC_VECTOR (7 DOWNTO 0); -- Procedimiento para NAND
        SIGNAL REN2 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)) IS

    BEGIN

        A <= (REN1 XNOR REN2);

        IF (A = zero) THEN
            flag(0) <= '1';
        ELSE
            flag(0) <= '0';
        END IF;

        IF (A > full) THEN
            flag(1) <= '1';
        ELSE
            flag(1) <= '0';
        END IF;

        IF (A < zero) THEN
            flag(2) <= '1';
        ELSE
            flag(2) <= '0';
        END IF;
    END LXNOR;

    PROCEDURE SLRAX (
        SIGNAL REN : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)
    ) IS

    BEGIN

        A <= '0' & REN(7 DOWNTO 1);

        IF (A = zero) THEN
            flag(0) <= '1';
        ELSE
            flag(0) <= '0';
        END IF;

        IF (A > full) THEN
            flag(1) <= '1';
        ELSE
            flag(1) <= '0';
        END IF;

        IF (A < zero) THEN
            flag(2) <= '1';
        ELSE
            flag(2) <= '0';
        END IF;
    END SLRAX;

    PROCEDURE SLLAX (
        SIGNAL REN : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        SIGNAL flag : OUT STD_LOGIC_VECTOR (2 DOWNTO 0);
        SIGNAL A : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0)) IS

    BEGIN

        A <= REN(7 DOWNTO 1) & '0';

        IF (A = zero) THEN
            flag(0) <= '1';
        ELSE
            flag(0) <= '0';
        END IF;

        IF (A > full) THEN
            flag(1) <= '1';
        ELSE
            flag(1) <= '0';
        END IF;

        IF (A < zero) THEN
            flag(2) <= '1';
        ELSE
            flag(2) <= '0';
        END IF;
    END SLLAX;

END nexysALU;