//===-- DylanLanguageRuntime.cpp -------------------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "lldb/Target/DylanLanguageRuntime.h"

#include <string.h>

#include "lldb/Core/PluginManager.h"
#include "lldb/Core/UniqueCStringMap.h"
#include "lldb/Target/ExecutionContext.h"

using namespace lldb;
using namespace lldb_private;

//----------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------
DylanLanguageRuntime::~DylanLanguageRuntime()
{
}

DylanLanguageRuntime::DylanLanguageRuntime (Process *process) :
    LanguageRuntime (process)
{
}

bool
DylanLanguageRuntime::GetObjectDescription (Stream &str, ValueObject &object)
{
    // Dylan has no generic way to do this.
    return false;
}

bool
DylanLanguageRuntime::GetObjectDescription (Stream &str, Value &value, ExecutionContextScope *exe_scope)
{
    // Dylan has no generic way to do this.
    return false;
}
