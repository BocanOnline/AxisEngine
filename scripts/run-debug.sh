#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
project_root="$(cd "${script_dir}/.." && pwd)"

cd "$project_root"

app="${1:-}"

case "$app" in
    laser)
        exec "./build/debug/source/AxisEngine-App-Laser/AxisEngine-App-Laser"     "${@:2}"
        ;;
    picker)
        exec "./build/debug/source/AxisEngine-App-Picker/AxisEngine-App-Picker"   "${@:2}"
        ;;
    plotter)
        exec "./build/debug/source/AxisEngine-App-Plotter/AxisEngine-App-Plotter" "${@:2}"
        ;;
    printer)
        exec "./build/debug/source/AxisEngine-App-Printer/AxisEngine-App-Printer" "${@:2}"
        ;;
    router)
        exec "./build/debug/source/AxisEngine-App-Router/AxisEngine-App-Router"   "${@:2}"
        ;;
    "")
        echo "Usage: $0 <app> [args...]"
        echo "Available apps: laser picker plotter printer router"
        exit 1
        ;;
    *)
        echo "Error: Unknown app '$app'"
        echo "Available apps: laser picker plotter printer router"
        exit 1
        ;;
esac
