# Git Push Instructions for vECU_Layer

## Initial Setup (First Time Only)

### 1. Initialize Git Repository

```bash
cd /home/minhtuan958/Documents/emtek/sdv/zonal_BSR_huynguyen/BabySafetyReminder/HIL_Realization/Phase3/Implementation/vehicle_computer/vECU_Layer

# Initialize git
git init

# Add remote repository
git remote add origin https://github.com/pmt563/fmu_BSR_old.git
```

### 2. Configure Git User (if not already configured)

```bash
git config user.name "Your Name"
git config user.email "your.email@example.com"
```

### 3. Add All Files

```bash
# Add all files (respecting .gitignore)
git add .

# Check what will be committed
git status
```

### 4. Create Initial Commit

```bash
git commit -m "Initial commit: vECU KUKSA connection with CI/CD pipeline

- Add Dockerfile for multi-architecture container builds
- Add GitHub Actions workflow for automated builds
- Add Python scripts for co-simulation and KUKSA integration
- Add FMU models for vECU components
- Add comprehensive documentation"
```

### 5. Push to GitHub

```bash
# Push to main branch
git push -u origin main

# If the repository already has content, you may need to force push (CAREFUL!)
# git push -u origin main --force
```

---

## Subsequent Updates

After the initial push, use these commands for updates:

```bash
# Check current status
git status

# Add modified files
git add .

# Or add specific files
git add src/host_cosim_and_connect_kuksa.py
git add Dockerfile

# Commit changes
git commit -m "Description of your changes"

# Push to GitHub
git push
```

---

## Verify GitHub Actions Workflow

After pushing, verify the CI/CD pipeline:

1. **Go to GitHub repository:**
   https://github.com/pmt563/fmu_BSR_old

2. **Click on "Actions" tab**

3. **Check workflow status:**
   - Should see "Build and Push Container Image" workflow running
   - Wait for it to complete (usually 5-10 minutes)

4. **Verify image was pushed:**
   - Go to repository main page
   - Look for "Packages" section on the right sidebar
   - Should see `fmu_bsr_old` package

5. **Pull and test the image:**
   ```bash
   podman pull ghcr.io/pmt563/fmu_bsr_old:latest
   podman run ghcr.io/pmt563/fmu_bsr_old:latest --help
   ```

---

## Troubleshooting

### Issue: "Permission denied" when pushing

**Solution:** Ensure you have write access to the repository
```bash
# Check remote URL
git remote -v

# If using HTTPS, you may need to authenticate
# Consider using SSH instead:
git remote set-url origin git@github.com:pmt563/fmu_BSR_old.git
```

### Issue: "Updates were rejected because the remote contains work"

**Solution:** Pull changes first, then push
```bash
git pull origin main --rebase
git push
```

### Issue: GitHub Actions workflow not running

**Solution:** 
1. Check repository settings → Actions → General
2. Ensure "Allow all actions and reusable workflows" is selected
3. Ensure workflow has "Read and write permissions"

### Issue: Container build fails in GitHub Actions

**Solution:** Check the Actions logs for specific errors
```bash
# Common issues:
# - Missing files (check .gitignore)
# - Dockerfile syntax errors
# - Missing dependencies in requirements.txt
```

---

## Enable GitHub Container Registry

If the package doesn't appear after successful workflow:

1. Go to repository Settings → Actions → General
2. Under "Workflow permissions", select:
   - ✅ Read and write permissions
   - ✅ Allow GitHub Actions to create and approve pull requests

3. Go to your GitHub profile → Settings → Developer settings → Personal access tokens
4. Ensure token has `write:packages` scope (if using personal token)

---

## Quick Reference

```bash
# Clone repository (for others)
git clone https://github.com/pmt563/fmu_BSR_old.git

# Pull latest image
podman pull ghcr.io/pmt563/fmu_bsr_old:latest

# Check image details
podman inspect ghcr.io/pmt563/fmu_bsr_old:latest

# View image layers
podman history ghcr.io/pmt563/fmu_bsr_old:latest
```
