################################################################################
# IO constraints
################################################################################
# serial:0.tx
set_property LOC D4 [get_ports {serial_tx}]
set_property IOSTANDARD LVCMOS33 [get_ports {serial_tx}]

# serial:0.rx
set_property LOC C4 [get_ports {serial_rx}]
set_property IOSTANDARD LVCMOS33 [get_ports {serial_rx}]

# clk:0
set_property LOC E3 [get_ports {clk}]
set_property IOSTANDARD LVCMOS33 [get_ports {clk}]

# cpu_reset:0
set_property LOC C12 [get_ports {cpu_reset}]
set_property IOSTANDARD LVCMOS33 [get_ports {cpu_reset}]

# led:0
set_property LOC T8 [get_ports {led0}]
set_property IOSTANDARD LVCMOS33 [get_ports {led0}]

# led:1
set_property LOC V9 [get_ports {led1}]
set_property IOSTANDARD LVCMOS33 [get_ports {led1}]

# led:2
set_property LOC R8 [get_ports {led2}]
set_property IOSTANDARD LVCMOS33 [get_ports {led2}]

# led:3
set_property LOC T6 [get_ports {led3}]
set_property IOSTANDARD LVCMOS33 [get_ports {led3}]

# sw:0
set_property LOC U9 [get_ports {sw0}]
set_property IOSTANDARD LVCMOS33 [get_ports {sw0}]

# sw:1
set_property LOC U8 [get_ports {sw1}]
set_property IOSTANDARD LVCMOS33 [get_ports {sw1}]

# sw:2
set_property LOC R7 [get_ports {sw2}]
set_property IOSTANDARD LVCMOS33 [get_ports {sw2}]

# sw:3
set_property LOC R6 [get_ports {sw3}]
set_property IOSTANDARD LVCMOS33 [get_ports {sw3}]

# btnc:0
set_property LOC E16 [get_ports {btnc}]
set_property IOSTANDARD LVCMOS33 [get_ports {btnc}]

# btnr:0
set_property LOC R10 [get_ports {btnr}]
set_property IOSTANDARD LVCMOS33 [get_ports {btnr}]

# btnd:0
set_property LOC V10 [get_ports {btnd}]
set_property IOSTANDARD LVCMOS33 [get_ports {btnd}]

# btnu:0
set_property LOC F15 [get_ports {btnu}]
set_property IOSTANDARD LVCMOS33 [get_ports {btnu}]

# btnud:0
set_property LOC D17 [get_ports {btnud}]
set_property IOSTANDARD LVCMOS33 [get_ports {btnud}]

# btnui:0
set_property LOC E17 [get_ports {btnui}]
set_property IOSTANDARD LVCMOS33 [get_ports {btnui}]

# btnut:0
set_property LOC G13 [get_ports {btnut}]
set_property IOSTANDARD LVCMOS33 [get_ports {btnut}]

# ledRGB:1.r
set_property LOC K6 [get_ports {ledRGB1_r}]
set_property IOSTANDARD LVCMOS33 [get_ports {ledRGB1_r}]

# ledRGB:1.g
set_property LOC H6 [get_ports {ledRGB1_g}]
set_property IOSTANDARD LVCMOS33 [get_ports {ledRGB1_g}]

# ledRGB:1.b
set_property LOC L16 [get_ports {ledRGB1_b}]
set_property IOSTANDARD LVCMOS33 [get_ports {ledRGB1_b}]

# ledRGB:2.r
set_property LOC K5 [get_ports {ledRGB2_r}]
set_property IOSTANDARD LVCMOS33 [get_ports {ledRGB2_r}]

# ledRGB:2.g
set_property LOC F13 [get_ports {ledRGB2_g}]
set_property IOSTANDARD LVCMOS33 [get_ports {ledRGB2_g}]

# ledRGB:2.b
set_property LOC F6 [get_ports {ledRGB2_b}]
set_property IOSTANDARD LVCMOS33 [get_ports {ledRGB2_b}]

# display_cs_n:0
set_property LOC N6 [get_ports {display_cs_n[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_cs_n[0]}]

# display_cs_n:0
set_property LOC M6 [get_ports {display_cs_n[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_cs_n[1]}]

# display_cs_n:0
set_property LOC M3 [get_ports {display_cs_n[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_cs_n[2]}]

# display_cs_n:0
set_property LOC N5 [get_ports {display_cs_n[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_cs_n[3]}]

# display_cs_n:0
set_property LOC N2 [get_ports {display_cs_n[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_cs_n[4]}]

# display_cs_n:0
set_property LOC N4 [get_ports {display_cs_n[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_cs_n[5]}]

# display_cs_n:0
set_property LOC L1 [get_ports {display_cs_n[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_cs_n[6]}]

# display_cs_n:0
set_property LOC M1 [get_ports {display_cs_n[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_cs_n[7]}]

# display_abcdefg:0
set_property LOC L3 [get_ports {display_abcdefg[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_abcdefg[0]}]

# display_abcdefg:0
set_property LOC N1 [get_ports {display_abcdefg[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_abcdefg[1]}]

# display_abcdefg:0
set_property LOC L5 [get_ports {display_abcdefg[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_abcdefg[2]}]

# display_abcdefg:0
set_property LOC L4 [get_ports {display_abcdefg[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_abcdefg[3]}]

# display_abcdefg:0
set_property LOC K3 [get_ports {display_abcdefg[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_abcdefg[4]}]

# display_abcdefg:0
set_property LOC M2 [get_ports {display_abcdefg[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_abcdefg[5]}]

# display_abcdefg:0
set_property LOC L6 [get_ports {display_abcdefg[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_abcdefg[6]}]

# display_abcdefg:0
set_property LOC M4 [get_ports {display_abcdefg[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {display_abcdefg[7]}]

# servo1:0
set_property LOC B13 [get_ports {servo1}]
set_property IOSTANDARD LVCMOS33 [get_ports {servo1}]

# servo2:0
set_property LOC F14 [get_ports {servo2}]
set_property IOSTANDARD LVCMOS33 [get_ports {servo2}]

# echo1:0
set_property LOC G14 [get_ports {echo1}]
set_property IOSTANDARD LVCMOS33 [get_ports {echo1}]

# trig1:0
set_property LOC P15 [get_ports {trig1}]
set_property IOSTANDARD LVCMOS33 [get_ports {trig1}]

# echo2:0
set_property LOC V11 [get_ports {echo2}]
set_property IOSTANDARD LVCMOS33 [get_ports {echo2}]

# trig2:0
set_property LOC V15 [get_ports {trig2}]
set_property IOSTANDARD LVCMOS33 [get_ports {trig2}]

# freq:0
set_property LOC K16 [get_ports {freq}]
set_property IOSTANDARD LVCMOS33 [get_ports {freq}]

################################################################################
# Design constraints
################################################################################

set_property INTERNAL_VREF 0.750 [get_iobanks 34]

################################################################################
# Clock constraints
################################################################################


################################################################################
# False path constraints
################################################################################


set_false_path -quiet -through [get_nets -hierarchical -filter {mr_ff == TRUE}]

set_false_path -quiet -to [get_pins -filter {REF_PIN_NAME == PRE} -of_objects [get_cells -hierarchical -filter {ars_ff1 == TRUE || ars_ff2 == TRUE}]]

set_max_delay 2 -quiet -from [get_pins -filter {REF_PIN_NAME == C} -of_objects [get_cells -hierarchical -filter {ars_ff1 == TRUE}]] -to [get_pins -filter {REF_PIN_NAME == D} -of_objects [get_cells -hierarchical -filter {ars_ff2 == TRUE}]]