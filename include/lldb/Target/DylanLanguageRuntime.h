//===-- DylanLanguageRuntime.h ---------------------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_DylanLanguageRuntime_h_
#define liblldb_DylanLanguageRuntime_h_

// C Includes
// C++ Includes
#include <vector>
// Other libraries and framework includes
// Project includes
#include "lldb/Core/PluginInterface.h"
#include "lldb/lldb-private.h"
#include "lldb/Target/LanguageRuntime.h"

namespace lldb_private {

class DylanLanguageRuntime :
    public LanguageRuntime
{
public:

    virtual
    ~DylanLanguageRuntime();

    lldb::LanguageType
    GetLanguageType () const override
    {
        return lldb::eLanguageTypeDylan;
    }

    bool
    GetObjectDescription (Stream &str, ValueObject &object) override;

    bool
    GetObjectDescription (Stream &str, Value &value, ExecutionContextScope *exe_scope) override;

protected:
    //------------------------------------------------------------------
    // Classes that inherit from DylanLanguageRuntime can see and modify these
    //------------------------------------------------------------------
    DylanLanguageRuntime(Process *process);
private:
    DISALLOW_COPY_AND_ASSIGN (DylanLanguageRuntime);
};

} // namespace lldb_private

#endif  // liblldb_DylanLanguageRuntime_h_
