from migen import *
from migen.genlib.cdc import MultiReg
from litex.soc.interconnect.csr import *
from litex.soc.interconnect.csr_eventmanager import *

#Modulo del Parlante
class parlante(Module,AutoCSR):
    def __init__(self,freq):
        self.clk = ClockSignal() #Relog

        self.max_cont = CSRStorage(29)
        self.enable = CSRStorage(1)

        self.freq = freq

        self.specials += Instance("parlante",
            i_clk = self.clk,
            i_max_cont = self.max_cont.storage,
            i_enable = self.enable.storage,
            o_freq = self.freq )