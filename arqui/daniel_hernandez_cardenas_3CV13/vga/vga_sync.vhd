LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
USE work.nexysClk.ALL;

ENTITY vga_sync IS
    PORT (
        vga_r : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
        vga_g : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
        vga_b : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
        vga_hs : OUT STD_LOGIC;
        vga_vs : OUT STD_LOGIC;
        LED : OUT STD_LOGIC;

        BTNU : IN STD_LOGIC;
        BTNL : IN STD_LOGIC;
        BTNR : IN STD_LOGIC;
        BTND : IN STD_LOGIC;
        figure : IN STD_LOGIC;
        clk : IN STD_LOGIC;
        reset : IN STD_LOGIC

        -- clk_out : out std_logic;
        -- hcnt : out unsigned(10 downto 0);
        -- vcnt : out unsigned(10 downto 0)
    );
END vga_sync;
ARCHITECTURE arch OF vga_sync IS

    SIGNAL pix_clock : STD_LOGIC;
    SIGNAL clk_2 : STD_LOGIC;
    SIGNAL mov_clockSig : STD_LOGIC := '0';

    SIGNAL h_cnt : unsigned(9 DOWNTO 0);
    SIGNAL v_cnt : unsigned(9 DOWNTO 0);
    SIGNAL squareHLimit : INTEGER := 370;
    SIGNAL squareHBegin : INTEGER := 270;
    SIGNAL squareVLimit : INTEGER := 250;
    SIGNAL squareVBegin : INTEGER := 150;
    SIGNAL circleHcenter : INTEGER := 320;
    SIGNAL circleVcenter : INTEGER := 200;
    SIGNAL circleRadiusSquare : INTEGER := 2500;
    -- SIGNAL circleSquareH : INTEGER := 0;
    -- SIGNAL circleSquareV : INTEGER := 0;
    -- SIGNAL inCircle : STD_LOGIC := '0';
    SIGNAL count : INTEGER := 1;

BEGIN

    sleepClk(clk, reset, 1, 1000000, count, mov_clockSig);

    clk_div_2 : PROCESS (clk, reset)
    BEGIN
        IF (reset = '0') THEN
            clk_2 <= '0';
        ELSIF rising_edge(clk) THEN
            clk_2 <= NOT clk_2;
        END IF;
    END PROCESS;

    pix_clk_gen : PROCESS (clk_2, reset)
    BEGIN
        IF (reset = '0') THEN
            pix_clock <= '0';
        ELSIF rising_edge(clk_2) THEN
            pix_clock <= NOT pix_clock;
        END IF;
    END PROCESS;

    -- checkCircle : PROCESS (pix_clock)
    -- BEGIN
    --     IF rising_edge(pix_clock) THEN
    --         circleSquareH <= (h_cnt - circleHcenter) * (h_cnt - circleHcenter);
    --         circleSquareV <= (v_cnt - circleVcenter) * (v_cnt - circleVcenter);
    --         IF circleSquareH < 0 THEN
    --             circleSquareH <= circleSquareH *- 1;
    --             END IF;
    --             IF circleSquareV < 0 THEN
    --             circleSquareV <= circleSquareV *- 1;
    --         END IF;

    --         inCircle <= (circleSquareV + circleVcenter) <= circleRadiusSquare;
    --     END IF;
    -- END PROCESS;

    move : PROCESS (mov_clockSig, reset)
    BEGIN
        IF (reset = '0') THEN
            squareHLimit <= 370;
            squareHBegin <= 270;
            squareVLimit <= 250;
            squareVBegin <= 150;
        ELSIF rising_edge(mov_clockSig) THEN
            IF (figure = '0') THEN

                IF (BTNU = '1') THEN
                    squareVLimit <= squareVLimit - 1;
                    squareVBegin <= squareVBegin - 1;

                END IF;
                IF (BTND = '1') THEN
                    squareVLimit <= squareVLimit + 1;
                    squareVBegin <= squareVBegin + 1;

                END IF;
                IF (BTNL = '1') THEN
                    squareHLimit <= squareHLimit - 1;
                    squareHBegin <= squareHBegin - 1;

                END IF;
                IF (BTNR = '1') THEN
                    squareHLimit <= squareHLimit + 1;
                    squareHBegin <= squareHBegin + 1;
                END IF;
            ELSE
                IF (BTNU = '1') THEN
                    circleVcenter <= circleVcenter - 1;
                ELSIF (BTND = '1') THEN
                    circleVcenter <= circleVcenter + 1;
                ELSIF (BTNL = '1') THEN
                    circleHcenter <= circleHcenter - 1;
                ELSIF (BTNR = '1') THEN
                    circleHcenter <= circleHcenter + 1;
                END IF;

            END IF;

        END IF;
    END PROCESS;

    vga_hs <= '0' WHEN h_cnt >= 656 AND h_cnt < 752 ELSE
        '1';
    vga_vs <= '1' WHEN v_cnt = 412 OR v_cnt = 413 ELSE
        '0';

    control : PROCESS (pix_clock, reset)
    BEGIN

        IF (reset = '0') THEN
            h_cnt <= to_unsigned(0, h_cnt'length);
            v_cnt <= to_unsigned(0, v_cnt'length);
        ELSIF rising_edge(pix_clock) THEN
            IF (h_cnt < 640 AND v_cnt < 400) THEN
                IF ((h_cnt > squareHBegin AND h_cnt < squareHLimit AND v_cnt > squareVBegin AND v_cnt < squareVLimit) OR
                    (((h_cnt - circleHcenter) * (h_cnt - circleHcenter) + ((v_cnt - circleVcenter) * (v_cnt - circleVcenter))) < circleRadiusSquare) OR
                    (((h_cnt - circleHcenter) * (h_cnt - circleHcenter) + ((circleVcenter - v_cnt) * (circleVcenter - v_cnt))) < circleRadiusSquare) OR
                    (((circleHcenter - h_cnt) * (circleHcenter - h_cnt) + ((circleVcenter - v_cnt) * (circleVcenter - v_cnt))) < circleRadiusSquare) OR
                    (((circleHcenter - h_cnt) * (circleHcenter - h_cnt) + ((v_cnt - circleVcenter) * (v_cnt - circleVcenter))) < circleRadiusSquare)
                    ) THEN
                    IF (h_cnt > 0 AND h_cnt < 320 AND v_cnt > 0 AND v_cnt < 200) THEN
                        vga_r <= X"F";
                        vga_g <= X"0";
                        vga_b <= X"F";
                    ELSIF (h_cnt > 0 AND h_cnt < 320 AND v_cnt > 200 AND v_cnt < 400) THEN
                        vga_r <= X"0";
                        vga_g <= X"F";
                        vga_b <= X"F";
                    ELSIF (h_cnt > 320 AND h_cnt < 640 AND v_cnt > 200 AND v_cnt < 400) THEN
                        vga_r <= X"F";
                        vga_g <= X"F";
                        vga_b <= X"0";
                    ELSE
                        vga_r <= X"F";
                        vga_g <= X"F";
                        vga_b <= X"F";
                    END IF;
                ELSE
                    vga_r <= X"0";
                    vga_g <= X"0";
                    vga_b <= X"0";
                END IF;
            ELSE
                vga_r <= X"0";
                vga_g <= X"0";
                vga_b <= X"0";
            END IF;

            IF (h_cnt < 800) THEN
                h_cnt <= h_cnt + 1;
            ELSE
                h_cnt <= to_unsigned(0, h_cnt'length);
                IF (v_cnt < 449) THEN
                    v_cnt <= v_cnt + 1;
                ELSE
                    v_cnt <= to_unsigned(0, v_cnt'length);
                END IF;
            END IF;
        END IF;
    END PROCESS;

    LED <= mov_clockSig;

END arch;