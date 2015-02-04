{
  "targets": [
    {
      "target_name": "lldb",
      "include_dirs": [ "../../include" ],
      "sources": [ "lldb_wrap.cxx" ],
      "conditions": [
        ["OS=='mac'", {
          "xcode_settings": {
            'INSTALL_PATH': '@rpath',
            'LD_DYLIB_INSTALL_NAME': '',
            "OTHER_CPLUSPLUSFLAGS" : ["-std=c++11", "-stdlib=libc++"],
            "MACOSX_DEPLOYMENT_TARGET" : "10.8",
            'OTHER_LDFLAGS': [
              '-Wl,-rpath,@loader_path/../../deps',
              '-F<(module_root_dir)/deps'
            ]
          },
          "link_settings" : { "libraries" : ["LLDB.framework"] }
        }],
        ["OS=='linux'", {
          "cflags_cc": [
            "-std=c++11",
            "-fexceptions"
          ],
          "link_settings" : { "libraries" : ["-llldb"] }
        }]
      ]
    }
  ]
}
