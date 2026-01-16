# vECU KUKSA Connection

[![Build and Push Container Image](https://github.com/pmt563/fmu_BSR_old/actions/workflows/build-and-push.yml/badge.svg)](https://github.com/pmt563/fmu_BSR_old/actions/workflows/build-and-push.yml)

Co-simulation environment for vECU (virtual ECU) with KUKSA VAL integration, containerized for multi-platform deployment.

## 🚀 Quick Start

### Pull Pre-built Image

```bash
# Pull latest image from GitHub Container Registry
podman pull ghcr.io/pmt563/fmu_bsr_old:latest

# Run with default KUKSA address (localhost:55555)
podman run ghcr.io/pmt563/fmu_bsr_old:latest

# Run with custom KUKSA address
podman run ghcr.io/pmt563/fmu_bsr_old:latest 192.168.1.100:55555
```

### Build Locally

```bash
# Build the container image
podman build -t vecu-kuksa:latest .

# Run locally built image
podman run vecu-kuksa:latest localhost:55555
```

## 📦 What's Inside

This container runs a co-simulation environment that:
- **Hosts FMU models**: vECU_Airbag, vecu_zonal, cockpit_test
- **Connects to KUKSA VAL**: Exchanges VSS (Vehicle Signal Specification) signals
- **Runs continuously**: 100 Hz simulation step (0.01s)

### VSS Signals

**Inputs (from KUKSA):**
- `Vehicle.Cabin.Seat.Row1.PassengerSide.Seating.Length`
- `Vehicle.Cabin.Light.Spotlight.Row1.PassengerSide.IsLightOn`
- `Vehicle.Cabin.Seat.Row1.PassengerSide.Position`

**Outputs (to KUKSA):**
- `Vehicle.Cabin.Seat.Row1.PassengerSide.Height`
- `Vehicle.Cabin.Seat.Row1.PassengerSide.Airbag.IsDeployed`
- `Vehicle.Cabin.Seat.Row1.PassengerSide.Massage`

## 🏗️ Architecture

```
┌─────────────────────────────────────────┐
│         Container (Multi-Arch)          │
│  ┌───────────────────────────────────┐  │
│  │  host_cosim_and_connect_kuksa.py  │  │
│  └───────────┬───────────────────────┘  │
│              │                           │
│      ┌───────┴────────┐                 │
│      ▼                ▼                  │
│  ┌────────┐    ┌──────────┐             │
│  │ CoSim  │    │  KUKSA   │             │
│  │ Thread │    │  Thread  │             │
│  └────┬───┘    └────┬─────┘             │
│       │             │                    │
│   ┌───▼──────┐  ┌───▼────────┐          │
│   │   FMUs   │  │ VSS Client │          │
│   └──────────┘  └────────────┘          │
└─────────────────────────────────────────┘
                    │
                    ▼
            ┌───────────────┐
            │  KUKSA VAL    │
            │  Data Broker  │
            └───────────────┘
```

## 🔧 Configuration

### Command-Line Arguments

```bash
podman run ghcr.io/pmt563/fmu_bsr_old:latest [KUKSA_ADDRESS]

# Examples:
podman run ghcr.io/pmt563/fmu_bsr_old:latest localhost:55555
podman run ghcr.io/pmt563/fmu_bsr_old:latest 192.168.1.100:55555
podman run ghcr.io/pmt563/fmu_bsr_old:latest host.containers.internal:55555
```

### Environment Variables

```bash
# Enable unbuffered Python output (already set in container)
podman run -e PYTHONUNBUFFERED=1 ghcr.io/pmt563/fmu_bsr_old:latest
```

## 🌍 Multi-Architecture Support

The container image supports:
- **linux/amd64** (x86_64) - Windows WSL2, Linux x86_64
- **linux/arm64** (aarch64) - ARM-based systems, Raspberry Pi

Docker/Podman automatically pulls the correct architecture for your system.

## 🤖 CI/CD Pipeline

Every push to `main` branch automatically:
1. ✅ Builds container for AMD64 and ARM64
2. ✅ Runs tests and validation
3. ✅ Pushes to GitHub Container Registry
4. ✅ Tags with `latest`, git SHA, and version

See [`.github/workflows/build-and-push.yml`](.github/workflows/build-and-push.yml) for details.

## 📚 Documentation

- **[README_CONTAINER.md](README_CONTAINER.md)** - Detailed container usage guide
- **[Dockerfile](Dockerfile)** - Container build configuration
- **[requirements.txt](requirements.txt)** - Python dependencies

## 🛠️ Development

### Local Development

```bash
# Install dependencies
pip install -r requirements.txt

# Run locally (without container)
cd src
python host_cosim_and_connect_kuksa.py localhost:55555
```

### Building Multi-Architecture Images

```bash
# Build for specific platform
podman build --platform linux/amd64 -t vecu-kuksa:amd64 .
podman build --platform linux/arm64 -t vecu-kuksa:arm64 .

# Build multi-arch manifest
podman build --platform linux/amd64,linux/arm64 --manifest vecu-kuksa:multi .
```

## 📝 License

[Add your license here]

## 🤝 Contributing

[Add contribution guidelines here]
