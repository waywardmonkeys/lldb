"""
Test process attach.
"""

import os, time
import unittest2
import lldb
from lldbtest import *
import lldbutil

exe_name = "ProcessAttach"  # Must match Makefile

class ProcessAttachTestCase(TestBase):

    mydir = TestBase.compute_mydir(__file__)

    @skipUnlessDarwin
    @dsym_test
    def test_attach_to_process_by_id_with_dsym(self):
        """Test attach by process id"""
        self.buildDsym()
        self.process_attach_by_id()

    @dwarf_test
    def test_attach_to_process_by_id_with_dwarf(self):
        """Test attach by process id"""
        self.buildDwarf()
        self.process_attach_by_id()

    @skipUnlessDarwin
    @dsym_test
    def test_attach_to_process_by_name_with_dsym(self):
        """Test attach by process name"""
        self.buildDsym()
        self.process_attach_by_name()

    @dwarf_test
    def test_attach_to_process_by_name_with_dwarf(self):
        """Test attach by process name"""
        self.buildDwarf()
        self.process_attach_by_name()

    def setUp(self):
        # Call super's setUp().
        TestBase.setUp(self)

    def tearDown(self):
        # Destroy process before TestBase.tearDown()
        self.dbg.GetSelectedTarget().GetProcess().Destroy()

        # Call super's tearDown().
        TestBase.tearDown(self)

    def process_attach_by_id(self):
        """Test attach by process id"""

        exe = os.path.join(os.getcwd(), exe_name)

        # Spawn a new process
        popen = self.spawnSubprocess(exe)
        self.addTearDownHook(self.cleanupSubprocesses)

        self.runCmd("process attach -p " + str(popen.pid))

        target = self.dbg.GetSelectedTarget()

        process = target.GetProcess()
        self.assertTrue(process, PROCESS_IS_VALID)


    def process_attach_by_name(self):
        """Test attach by process name"""

        exe = os.path.join(os.getcwd(), exe_name)

        # Spawn a new process
        popen = self.spawnSubprocess(exe)
        self.addTearDownHook(self.cleanupSubprocesses)

        self.runCmd("process attach -n " + exe_name)

        target = self.dbg.GetSelectedTarget()

        process = target.GetProcess()
        self.assertTrue(process, PROCESS_IS_VALID)


if __name__ == '__main__':
    import atexit
    lldb.SBDebugger.Initialize()
    atexit.register(lambda: lldb.SBDebugger.Terminate())
    unittest2.main()
