#!/usr/bin/env python3
import argparse
from pathlib import Path

PART = "xc7k160tfbg484-1"
CLOCK = 10
KERNELS = [f"kernel{i}" for i in range(1, 11)]


def make_config(kernel: str, kernel_dir: Path) -> str:
    cpp = kernel_dir / f"{kernel}.cpp"
    h = kernel_dir / f"{kernel}.h"
    tb = kernel_dir / f"{kernel}_test.cpp"
    return (
        f"part={PART}\n"
        f"\n"
        f"[hls]\n"
        f"flow_target=vivado\n"
        f"package.output.format=ip_catalog\n"
        f"package.output.syn=false\n"
        f"syn.top={kernel}\n"
        f"syn.file={cpp}\n"
        f"syn.file={h}\n"
        f"tb.file={tb}\n"
        f"clock={CLOCK}\n"
        f"syn.compile.pipeline_loops=0\n"
    )


def make_setup(workspace: Path, kernels: list[str], new_api: bool) -> str:
    workspace_call = "update_workspace" if new_api else "set_workspace"
    lines = [
        "import vitis",
        "",
        "client = vitis.create_client()",
        f'client.{workspace_call}(path="{workspace}")',
        "",
    ]
    for kernel in kernels:
        cfg_path = workspace / kernel / "hls_config.cfg"
        lines.append(
            f'comp = client.create_hls_component('
            f'name="hls-cmp-{kernel}", '
            f'cfg_file=["{cfg_path}"])'
        )
    lines += ["", "vitis.dispose()", ""]
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--new-api",
        action="store_true",
        help="use update_workspace instead of set_workspace (Vitis 2024.2+)",
    )
    args = parser.parse_args()

    cwd = Path.cwd()
    present = []
    for kernel in KERNELS:
        kernel_dir = cwd / kernel
        if not kernel_dir.is_dir():
            print(f"skip: {kernel_dir} does not exist")
            continue
        out_file = kernel_dir / "hls_config.cfg"
        out_file.write_text(make_config(kernel, kernel_dir))
        print(f"wrote {out_file}")
        present.append(kernel)

    setup_file = cwd / "setup.py"
    setup_file.write_text(make_setup(cwd, present, args.new_api))
    print(f"wrote {setup_file}")


if __name__ == "__main__":
    main()
