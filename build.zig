const std = @import("std");

pub fn build(b: *std.build.Builder) void {
    const target = b.standardTargetOptions(.{});
    const optimization = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "enigma",
        .target = target,
        .optimize = optimization,
    });
    exe.linkLibCpp();
    exe.force_pic = true;
    exe.addCSourceFiles(&.{
        "examples/main.cpp",
        "src/enigma/enigma.cpp",
        "src/enigma/generator.cpp",
        "src/enigma/plugboard.cpp",
        "src/enigma/reflector.cpp",
        "src/enigma/rotor.cpp",
    }, &.{
        "-std=c++11",
        "-Wall",
        "-W",
        "-Wstrict-prototypes",
        "-Wwrite-strings",
        "-Wno-missing-field-initializers",
    });
    b.installArtifact(exe);

    const pylib = b.addSharedLibrary(.{
        .name = "enigma",
        .target = target,
        .optimize = optimization,
    });
    pylib.linkLibCpp();
    pylib.linkLibC();
    pylib.force_pic = true;
    pylib.addCSourceFiles(&.{
        "src/enigma_py/libenigma.cpp",
        "src/enigma/enigma.cpp",
        "src/enigma/generator.cpp",
        "src/enigma/plugboard.cpp",
        "src/enigma/reflector.cpp",
        "src/enigma/rotor.cpp",
    }, &.{
        "-std=c++11",
        "-Wall",
        "-O3",
        "-I/usr/include/python3.11",
        "-o libenigma$(python3-config --extension-suffix)",
    });
    b.installArtifact(pylib);
}
