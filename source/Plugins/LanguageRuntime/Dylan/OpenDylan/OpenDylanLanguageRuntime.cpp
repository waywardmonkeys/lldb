//===-- OpenDylanLanguageRuntime.cpp --------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "OpenDylanLanguageRuntime.h"

#include "lldb/Breakpoint/BreakpointLocation.h"
#include "lldb/Core/ConstString.h"
#include "lldb/Core/Error.h"
#include "lldb/Core/Log.h"
#include "lldb/Core/Module.h"
#include "lldb/Core/PluginManager.h"
#include "lldb/Core/Scalar.h"
#include "lldb/Symbol/Symbol.h"
#include "lldb/Symbol/TypeList.h"
#include "lldb/Target/Process.h"
#include "lldb/Target/StopInfo.h"
#include "lldb/Target/Target.h"

#include <vector>

using namespace lldb;
using namespace lldb_private;

//------------------------------------------------------------------
// Static Functions
//------------------------------------------------------------------
LanguageRuntime *
OpenDylanLanguageRuntime::CreateInstance (Process *process, lldb::LanguageType language)
{
    if (language == eLanguageTypeDylan)
        return new OpenDylanLanguageRuntime(process);
    else
        return NULL;
}

void
OpenDylanLanguageRuntime::Initialize ()
{
    PluginManager::RegisterPlugin(GetPluginNameStatic(),
                                  "Open Dylan ABI for the Dylan language",
                                  CreateInstance);
}

void
OpenDylanLanguageRuntime::Terminate ()
{
    PluginManager::UnregisterPlugin(CreateInstance);
}

lldb_private::ConstString
OpenDylanLanguageRuntime::GetPluginNameStatic()
{
    static ConstString g_name("opendylan");
    return g_name;
}

//------------------------------------------------------------------
// PluginInterface protocol
//------------------------------------------------------------------
lldb_private::ConstString
OpenDylanLanguageRuntime::GetPluginName ()
{
    return GetPluginNameStatic();
}

uint32_t
OpenDylanLanguageRuntime::GetPluginVersion ()
{
    return 1;
}

BreakpointResolverSP
OpenDylanLanguageRuntime::CreateExceptionResolver (Breakpoint *bkpt, bool catch_bp, bool throw_bp)
{
    // FIXME: Modify the runtime to have a function we can break on for catch
    static const char *g_catch_name = "";
    static const char *g_throw_name = "KsignalVKdMM0I";
    std::vector<std::string> exception_names;
    exception_names.reserve(2);
    if (catch_bp)
    {
        exception_names.push_back(g_catch_name);
    }

    if (throw_bp)
    {
        exception_names.push_back(g_throw_name);
    }

    BreakpointResolverSP resolver_sp (new BreakpointResolverName(bkpt,
                                                                 exception_names,
                                                                 eFunctionNameTypeBase,
                                                                 eLanguageTypeUnknown,
                                                                 eLazyBoolNo));

    return resolver_sp;
}

lldb::SearchFilterSP
OpenDylanLanguageRuntime::CreateExceptionSearchFilter ()
{
    return LanguageRuntime::CreateExceptionSearchFilter();
}

void
OpenDylanLanguageRuntime::SetExceptionBreakpoints ()
{
    const bool catch_bp = false;
    const bool throw_bp = true;
    const bool is_internal = true;

    if (!m_dylan_exception_bp_sp)
    {
        m_dylan_exception_bp_sp = LanguageRuntime::CreateExceptionBreakpoint(m_process->GetTarget(),
                                                                             GetLanguageType(),
                                                                             catch_bp,
                                                                             throw_bp,
                                                                             is_internal);
        if (m_dylan_exception_bp_sp)
        {
            m_dylan_exception_bp_sp->SetBreakpointKind("Dylan condition");
        }
    }
    else
    {
        m_dylan_exception_bp_sp->SetEnabled(true);
    }
}

void
OpenDylanLanguageRuntime::ClearExceptionBreakpoints ()
{
    if (!m_process)
    {
        return;
    }

    if (m_dylan_exception_bp_sp)
    {
        m_dylan_exception_bp_sp->SetEnabled(false);
    }
}

bool
OpenDylanLanguageRuntime::ExceptionBreakpointsAreSet ()
{
    return m_dylan_exception_bp_sp && m_dylan_exception_bp_sp->IsEnabled();
}

bool
OpenDylanLanguageRuntime::ExceptionBreakpointsExplainStop (lldb::StopInfoSP stop_reason)
{
    if (!m_process)
    {
        return false;
    }

    if (!stop_reason || stop_reason->GetStopReason() != eStopReasonBreakpoint)
    {
        return false;
    }

    uint64_t break_site_id = stop_reason->GetValue();
    return m_process->GetBreakpointSiteList().BreakpointSiteContainsBreakpoint(break_site_id,
                                                                               m_dylan_exception_bp_sp->GetID());

}

bool
OpenDylanLanguageRuntime::CouldHaveDynamicValue (ValueObject &in_value)
{
    return false;
}

bool
OpenDylanLanguageRuntime::GetDynamicTypeAndAddress (ValueObject &in_value,
                                                    lldb::DynamicValueType use_dynamic,
                                                    TypeAndOrName &class_type_or_name,
                                                    Address &dynamic_address)
{
    return false;
}
