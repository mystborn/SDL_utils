project('SDL_utils', 'c')

c_comp = meson.get_compiler('c')

cpus = {
    'aarch64' : 'x64',
    'arc' : 'x86',
    'arm' : 'x86',
    'ia64' : 'x64',
    'mips' : 'x86',
    'mips64' : 'x64',
    'ppc' : 'x86',
    'ppc64' : 'x64',
    'riscv32' : 'x86',
    'riscv64' : 'x64',
    'rx' : 'x86',
    'sparc' : 'x86',
    'sparc64' : 'x64',
    'wasm32' : 'x86',
    'wasm64' : 'x64',
    'x86' : 'x86',
    'x86_64' : 'x64'
}

cpu = cpus.get(target_machine.cpu_family())
include_files = ['include']

if c_comp.has_header('SDL.h')
    sdl = c_comp.find_library('SDL2',
        required: true)
else
    sdl_dir = get_option('sdl_dir')
    if(sdl_dir == '')
        sdl = disabler()
    else
        include_files += sdl_dir + '/include'

        message(sdl_dir + '/lib/' + cpu)
    
        sdl = c_comp.find_library('SDL2',
            required: true,
            dirs: sdl_dir + '/lib/' + cpu
        )
    endif
endif

myst_ecs = subproject('MystEcs')

deps = [
    sdl,
    myst_ecs.get_variable('myst_ecs_dep')
]

inc = include_directories(include_files)
subdir('src')

sdl_utils = static_library('SDL_utils',
    sources,
    include_directories: inc,
    dependencies: deps,
    install: true,
    name_suffix: 'lib',
    name_prefix: ''
)

sdl_utils_shared = shared_library('SDL_utils',
    sources,
    include_directories: inc,
    dependencies: deps,
    install: true
)

sdl_utils_dep = declare_dependency(include_directories: inc,
    link_with: sdl_utils_shared,
    dependencies: deps
)