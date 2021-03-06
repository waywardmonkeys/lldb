"""Test SBValue::Persist"""

import os, sys, time
import unittest2
import lldb
from lldbtest import *
import lldbutil

class SBValuePersistTestCase(TestBase):

    mydir = TestBase.compute_mydir(__file__)

    @skipUnlessDarwin
    @python_api_test
    @dsym_test
    def test_with_dsym(self):
        """Test SBValue::Persist"""
        self.buildDsym()
        self.setTearDownCleanup()
        self.doTest()

    @python_api_test
    @dwarf_test
    def test_with_dwarf(self):
        """Test SBValue::Persist"""
        self.buildDwarf()
        self.setTearDownCleanup()
        self.doTest()

    def setUp(self):
        # Call super's setUp().
        TestBase.setUp(self)

    def doTest(self):
        """Test SBValue::Persist"""
        self.runCmd("file a.out", CURRENT_EXECUTABLE_SET)

        lldbutil.run_break_set_by_source_regexp (self, "break here")

        self.runCmd("run", RUN_SUCCEEDED)

        # The stop reason of the thread should be breakpoint.
        self.expect("thread list", STOPPED_DUE_TO_BREAKPOINT,
            substrs = ['stopped',
                       'stop reason = breakpoint'])
        
        # This is the function to remove the custom formats in order to have a
        # clean slate for the next test case.
        def cleanup():
            self.runCmd('type format clear', check=False)
            self.runCmd('type summary clear', check=False)
            self.runCmd('type filter clear', check=False)
            self.runCmd('type synthetic clear', check=False)

        # Execute the cleanup function during test case tear down.
        self.addTearDownHook(cleanup)

        foo = self.frame().FindVariable("foo")
        bar = self.frame().FindVariable("bar")
        baz = self.frame().FindVariable("baz")

        self.assertTrue(foo.IsValid(), "foo is not valid")
        self.assertTrue(bar.IsValid(), "bar is not valid")
        self.assertTrue(baz.IsValid(), "baz is not valid")
        
        fooPersist = foo.Persist()
        barPersist = bar.Persist()
        bazPersist = baz.Persist()

        self.assertTrue(fooPersist.IsValid(), "fooPersist is not valid")
        self.assertTrue(barPersist.IsValid(), "barPersist is not valid")
        self.assertTrue(bazPersist.IsValid(), "bazPersist is not valid")

        self.assertTrue(fooPersist.GetValueAsUnsigned(0) == 10, "fooPersist != 10")
        self.assertTrue(barPersist.GetPointeeData().sint32[0] == 4, "barPersist != 4")
        self.assertTrue(bazPersist.GetSummary() == '"85"', "bazPersist != 85")
        
        self.runCmd("continue")

        self.assertTrue(fooPersist.IsValid(), "fooPersist is not valid")
        self.assertTrue(barPersist.IsValid(), "barPersist is not valid")
        self.assertTrue(bazPersist.IsValid(), "bazPersist is not valid")

        self.assertTrue(fooPersist.GetValueAsUnsigned(0) == 10, "fooPersist != 10")
        self.assertTrue(barPersist.GetPointeeData().sint32[0] == 4, "barPersist != 4")
        self.assertTrue(bazPersist.GetSummary() == '"85"', "bazPersist != 85")
        
        self.expect("expr *(%s)" % (barPersist.GetName()), substrs = ['= 4'])

if __name__ == '__main__':
    import atexit
    lldb.SBDebugger.Initialize()
    atexit.register(lambda: lldb.SBDebugger.Terminate())
    unittest2.main()
