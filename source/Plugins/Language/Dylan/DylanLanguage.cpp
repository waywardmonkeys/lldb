//===-- DylanLanguage.cpp --------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "DylanLanguage.h"

#include "lldb/Core/ConstString.h"
#include "lldb/Core/PluginManager.h"

using namespace lldb;
using namespace lldb_private;

void
DylanLanguage::Initialize()
{
    PluginManager::RegisterPlugin (GetPluginNameStatic(),
                                   "Dylan Language",
                                   CreateInstance);
}

void
DylanLanguage::Terminate()
{
    PluginManager::UnregisterPlugin (CreateInstance);
}

lldb_private::ConstString
DylanLanguage::GetPluginNameStatic()
{
    static ConstString g_name("objc");
    return g_name;
}


//------------------------------------------------------------------
// PluginInterface protocol
//------------------------------------------------------------------
lldb_private::ConstString
DylanLanguage::GetPluginName()
{
    return GetPluginNameStatic();
}

uint32_t
DylanLanguage::GetPluginVersion()
{
    return 1;
}

//------------------------------------------------------------------
// Static Functions
//------------------------------------------------------------------
Language *
DylanLanguage::CreateInstance (lldb::LanguageType language)
{
    switch (language)
    {
        case lldb::eLanguageTypeDylan:
            return new DylanLanguage();
        default:
            return nullptr;
    }
}
