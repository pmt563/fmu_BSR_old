# Windows Container Build and Usage Guide

## 📋 Overview

This Windows container uses the existing FMU Windows DLL binaries (no compilation needed).

## 🏗️ Building the Container

### Prerequisites
- **Windows 10/11** or **Windows Server 2019/2022**
- **Docker Desktop** with Windows containers enabled
- Or **Podman** for Windows

### Switch to Windows Containers

**Docker Desktop:**
1. Right-click Docker icon in system tray
2. Select "Switch to Windows containers..."

**Podman:**
```powershell
# Podman supports Windows containers natively
```

### Build Command

```powershell
# Using Docker
docker build -f Dockerfile.windows -t vecu-kuksa:windows .

# Using Podman
podman build -f Dockerfile.windows -t vecu-kuksa:windows .
```

**Build time:** ~10-15 minutes (first time, downloads Python installer)

## 🚀 Running the Container

### Basic Usage

```powershell
# Run with default KUKSA address (localhost:55555)
docker run vecu-kuksa:windows

# Run with custom KUKSA address
docker run vecu-kuksa:windows 192.168.1.100:55555

# Run with host machine address
docker run vecu-kuksa:windows host.docker.internal:55555
```

### Advanced Usage

**Run in detached mode:**
```powershell
docker run -d --name vecu-kuksa vecu-kuksa:windows 192.168.1.100:55555

# View logs
docker logs -f vecu-kuksa

# Stop container
docker stop vecu-kuksa

# Remove container
docker rm vecu-kuksa
```

**Interactive mode (for debugging):**
```powershell
docker run -it vecu-kuksa:windows cmd
# Inside container:
C:\app\src> python host_cosim_and_connect_kuksa.py localhost:55555
```

## 📦 Container Details

**Base Image:** `mcr.microsoft.com/windows/servercore:ltsc2022`
- Size: ~5-6 GB (Windows base is large)
- Python: 3.11.9
- Architecture: AMD64 only

**Included:**
- Python 3.11.9
- All Python dependencies (fmpy, matplotlib, kuksa-client, numpy)
- FMU files with Windows DLL binaries
- Application source code

## 🔧 GitHub Actions for Windows Container

Update `.github/workflows/build-and-push.yml` to build Windows container:

```yaml
name: Build and Push Windows Container

on:
  push:
    branches: [main]
  workflow_dispatch:

jobs:
  build-windows:
    runs-on: windows-latest
    
    steps:
      - name: Checkout
        uses: actions/checkout@v4
      
      - name: Login to GitHub Container Registry
        uses: docker/login-action@v3
        with:
          registry: ghcr.io
          username: ${{ github.actor }}
          password: ${{ secrets.GITHUB_TOKEN }}
      
      - name: Build and push
        run: |
          docker build -f Dockerfile.windows -t ghcr.io/${{ github.repository }}:windows .
          docker push ghcr.io/${{ github.repository }}:windows
```

## 🌐 Multi-Platform Strategy

Since Windows and Linux containers are separate:

**Option 1: Separate Images**
```powershell
# Pull Windows image
docker pull ghcr.io/pmt563/fmu_bsr_old:windows

# Pull Linux image (when available)
docker pull ghcr.io/pmt563/fmu_bsr_old:linux
```

**Option 2: Manifest List** (Advanced)
```powershell
# Create manifest combining both
docker manifest create ghcr.io/pmt563/fmu_bsr_old:latest `
  ghcr.io/pmt563/fmu_bsr_old:windows `
  ghcr.io/pmt563/fmu_bsr_old:linux
```

## ⚠️ Important Notes

### Windows Container Limitations

1. **Size:** Windows containers are large (~5-6 GB vs ~500 MB for Linux)
2. **Host OS:** Must run on Windows host (cannot run on Linux)
3. **Architecture:** AMD64 only (no ARM64 support)

### Networking

**Access host machine:**
```powershell
docker run vecu-kuksa:windows host.docker.internal:55555
```

**Custom network:**
```powershell
docker network create vecu-network
docker run --network vecu-network vecu-kuksa:windows kuksa-broker:55555
```

## 🐛 Troubleshooting

### Issue: "image operating system "windows" cannot be used on this platform"

**Solution:** Switch Docker to Windows containers mode
```powershell
# Docker Desktop
# Right-click tray icon → "Switch to Windows containers"
```

### Issue: Python not found

**Solution:** Rebuild without cache
```powershell
docker build --no-cache -f Dockerfile.windows -t vecu-kuksa:windows .
```

### Issue: FMU files not loading

**Solution:** Verify FMU files are in container
```powershell
docker run -it vecu-kuksa:windows cmd
C:\app> dir fmus
C:\app> dir fmus\*.fmu
```

### Issue: Container too large

**Solution:** Use Windows Nano Server (smaller but more limited)
```dockerfile
FROM mcr.microsoft.com/windows/nanoserver:ltsc2022
# Note: Requires different Python installation method
```

## 📊 Comparison: Windows vs Linux Container

| Feature | Windows Container | Linux Container |
|---------|------------------|-----------------|
| Base Image Size | ~5-6 GB | ~500 MB |
| FMU Support | ✅ Native DLL | ❌ Needs .so compilation |
| Host OS | Windows only | Linux, Windows (WSL2) |
| Architecture | AMD64 only | AMD64, ARM64 |
| Build Time | ~10-15 min | ~5-10 min |
| Ease of Setup | ✅ Simple | ❌ Complex (compilation) |

## ✅ Recommended Workflow

**For Windows users:**
1. Use `Dockerfile.windows` - simple and works immediately
2. Build and run on Windows host
3. Push to ghcr.io with `:windows` tag

**For Linux users:**
1. Request Linux FMU binaries from FMU creator
2. Or wait for cross-compilation solution
3. Use `:linux` tag when available

## 📚 Additional Resources

- [Windows Container Documentation](https://docs.microsoft.com/en-us/virtualization/windowscontainers/)
- [Docker Desktop for Windows](https://docs.docker.com/desktop/windows/)
- [Microsoft Container Registry](https://mcr.microsoft.com/)
