//===-- OpenDylanLanguageRuntime.h ----------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_OpenDylanLanguageRuntime_h_
#define liblldb_OpenDylanLanguageRuntime_h_

// C Includes
// C++ Includes
// Other libraries and framework includes
// Project includes
#include "lldb/lldb-private.h"
#include "lldb/Breakpoint/BreakpointResolver.h"
#include "lldb/Target/DylanLanguageRuntime.h"
#include "lldb/Target/LanguageRuntime.h"
#include "lldb/Core/Value.h"

namespace lldb_private {

    class OpenDylanLanguageRuntime :
    public lldb_private::DylanLanguageRuntime
    {
    public:
        ~OpenDylanLanguageRuntime () { }

        //------------------------------------------------------------------
        // Static Functions
        //------------------------------------------------------------------
        static void
        Initialize ();

        static void
        Terminate ();

        static lldb_private::LanguageRuntime *
        CreateInstance (Process *process, lldb::LanguageType language);

        static lldb_private::ConstString
        GetPluginNameStatic ();

        //------------------------------------------------------------------
        // PluginInterface protocol
        //------------------------------------------------------------------
        lldb_private::ConstString
        GetPluginName () override;

        uint32_t
        GetPluginVersion () override;

        void
        SetExceptionBreakpoints () override;

        void
        ClearExceptionBreakpoints () override;

        bool
        ExceptionBreakpointsAreSet () override;

        bool
        ExceptionBreakpointsExplainStop (lldb::StopInfoSP stop_reason) override;

        lldb::BreakpointResolverSP
        CreateExceptionResolver (Breakpoint *bkpt, bool catch_bp, bool throw_bp) override;

        lldb::SearchFilterSP
        CreateExceptionSearchFilter () override;

        bool
        GetDynamicTypeAndAddress (ValueObject &in_value,
                                  lldb::DynamicValueType use_dynamic,
                                  TypeAndOrName &class_type_or_name,
                                  Address &address) override;

        bool
        CouldHaveDynamicValue (ValueObject &in_value) override;

    private:
        OpenDylanLanguageRuntime(Process *process) : lldb_private::DylanLanguageRuntime(process) { } // Call CreateInstance instead.

        lldb::BreakpointSP                              m_dylan_exception_bp_sp;
    };

} // namespace lldb_private

#endif  // liblldb_OpenDylanLanguageRuntime_h_
