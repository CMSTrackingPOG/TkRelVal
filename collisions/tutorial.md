# TkRelVal – Tracking RelVal DQM Comparisons (CMSSW_14_0_0)

TkRelVal is a lightweight framework to **compare RelVal DQM ROOT files** (reference vs target), produce validation plots, and **publish the results** under the standard CMS Tracking Validation web area.

It acts mainly as an **orchestrator** on top of existing tracking validation tools: it takes care of file organization, labeling, web-page updates, and then calls the core plotting scripts.

Two workflows are supported:
- **Manual workflow** (recommended and robust)
- **Automatic workflow using `helper.py`** (experimental, authentication-dependent)

---

## 1. What this framework does

The actual histogram comparison is performed by the existing validation scripts (in particular `makeValidationPlots.sh`), which compare histograms inside DQM ROOT files.

TkRelVal adds:
- automatic parsing of **run / era / release / sample** from filenames
- consistent **labels** for reference and target
- creation of the correct **EOS directory structure**
- automatic update of the tracking validation **`index.html`**
- optional automation of file discovery and download

High-level flow:
1. Select a **reference** and a **target** DQM ROOT file.
2. Run `start.py`, which:
   - validates run/era/sample consistency
   - builds the output folder name
   - updates the tracking validation web page
   - computes luminosity via `LumiCalc`
   - calls `makeValidationPlots.sh` to generate plots
3. Results are written under EOS and immediately visible on the validation webpage.

---

## 2. Requirements

### 2.1 CMSSW release

TkRelVal is intended to run in **CMSSW_14_0_0**:

```bash
cmsrel CMSSW_14_0_0
cd CMSSW_14_0_0/src
cmsenv
```

### 2.2 EOS access

Results are written to the official tracking validation area:

```text
/eos/project/c/cmsweb/www/tracking/validation/DATA/
```

You must have **write permissions** to this area.

### 2.3 GRID proxy (required to download files)

Downloading DQM files from `cmsweb.cern.ch` requires a valid CMS proxy:

```bash
voms-proxy-init -voms cms -rfc --valid 168:0
export X509_USER_PROXY=$(voms-proxy-info -path)
voms-proxy-info -timeleft
```

---

## 3. Installation

From `CMSSW_14_0_0/src`:

```bash
git clone <REPOSITORY_URL> TkRelVal
cd TkRelVal
```

Compilation is usually not required, but safe to do:

```bash
scram b -j 8
```

---

## 4. Recommended setup: DQM symlink

To simplify file handling and ensure results are written directly to EOS, create a symbolic link:

```bash
cd $CMSSW_BASE/src/TkRelVal/collisions
ln -s /eos/project/c/cmsweb/www/tracking/validation/DATA/DQM DQM
ls -l DQM
```

Expected output:

```text
DQM -> /eos/project/c/cmsweb/www/tracking/validation/DATA/DQM
```

---

## 5. Manual workflow (recommended)

This is the most robust and transparent way to use TkRelVal.

### 5.1 Step 1 — Download the DQM ROOT files

Use the provided script `GetFiles.sh` to download DQM ROOT files from the RelVal browser.

**Usage**

```bash
./GetFiles.sh <web_dir> <run> <rel> <sample> [add_key] [optional_arg]
```

**Arguments**
- `web_dir`: directory used by the DQM RelVal browser (e.g. `CMSSW_14_0_0_pre5/`)
- `run`: run number (e.g. `367131`)
- `rel`: release string used in filename matching
- `sample`: e.g. `ZeroBias`
- `add_key`, `optional_arg`: optional wildcards (default: `*`)

**Example**

```bash
cd $CMSSW_BASE/src/TkRelVal
export X509_USER_PROXY=$(voms-proxy-info -path)

# Reference
./GetFiles.sh CMSSW_15_0_x 382229 15_0_0_pre3 ZeroBias

# Target
./GetFiles.sh CMSSW_15_1_x 382229 15_1_0_pre1 ZeroBias
```

Downloaded files are moved automatically to:

```text
DQM/<web_dir>/<rel>/<run>/<sample>/
```
---

### 5.2 Step 2 — Run the comparison (`start.py`)

`start.py` is the main entry point for running comparisons and publishing results.

It:
- validates run / era / sample consistency
- computes labels and folder names
- updates `index.html` on EOS
- computes luminosity via `LumiCalc`
- calls `makeValidationPlots.sh`

**Usage**

```bash
python3 start.py \
  --refFile <PATH/TO/REFERENCE.root> \
  --targetFile <PATH/TO/TARGET.root> \
  --refLabel <refLabel> \
  --targetLabel <targetLabel> \
  --FullPlots
```

**Example**

```bash
python3 start.py \
  --refFile    $CMSSW_BASE/src/TkRelVal/collisions/DQM/CMSSW_14_0_0_pre4/CMSSW_14_0_0_pre4/367131/ZeroBias/REF.root \
  --targetFile $CMSSW_BASE/src/TkRelVal/collisions/DQM/CMSSW_14_0_0_pre5/CMSSW_14_0_0_pre5/367131/ZeroBias/TAR.root \
  --refLabel   14_0_0_pre4 \
  --targetLabel 14_0_0_pre5 \
  --FullPlots
```

After completion, the comparison appears automatically on the tracking validation webpage.

---

## 6. Automatic workflow (`helper.py`) – optional

`helper.py` was designed to fully automate the workflow:
1. Read a RelVal report web page
2. Extract target/reference releases and Global Tags
3. Query the DQM RelVal browser
4. Download candidate ROOT files
5. Run comparisons automatically via `start.py`

**Important:** this workflow relies on Kerberos / SSO authentication and may fail depending on your setup. If authentication fails, use the manual workflow instead.

**Usage**

```bash
cd $CMSSW_BASE/src/TkRelVal
cmsenv
export X509_USER_PROXY=$(voms-proxy-info -path)

python3 helper.py "<URL_TO_RELVAL_REPORT_PAGE>"
```

---

## 7. How the pieces fit together

- **`GetFiles.sh`**  
  Downloads DQM ROOT files from cmsweb and places them in the correct directory structure.

- **`start.py`**  
  Organizes the comparison, updates the web index, computes luminosity, and calls the core plotting script.

- **`makeValidationPlots.sh`**  
  The real core: extracts histograms and produces the comparison plots.

- **`helper.py`**  
  Optional automation layer (scraping + orchestration).

---

## 8. Troubleshooting

### 8.1 Proxy errors

```bash
voms-proxy-init -voms cms -rfc --valid 168:0
export X509_USER_PROXY=$(voms-proxy-info -path)
voms-proxy-info -timeleft
```

### 8.2 Run / era mismatch

Ensure reference and target files correspond to the **same run** and, ideally, the **same era**.

### 8.3 Files already present under a different folder

The framework may re-download files to enforce a consistent directory structure. This is expected behavior in some edge cases.

---

## 9. Quick start (copy/paste)

```bash
# setup
cmsrel CMSSW_14_0_0
cd CMSSW_14_0_0/src
cmsenv
git clone <REPOSITORY_URL> TkRelVal

# symlink
cd TkRelVal
ln -s /eos/project/c/cmsweb/www/tracking/validation/DATA/DQM DQM

cd collisions
ln -s /eos/project/c/cmsweb/www/tracking/validation/DATA/DQM DQM

# proxy
voms-proxy-init -voms cms -rfc --valid 168:0
export X509_USER_PROXY=$(voms-proxy-info -path)

# download
cd $CMSSW_BASE/src/TkRelVal
./GetFiles.sh <web_dir_ref> <run> <rel_ref> <sample>
./GetFiles.sh <web_dir_tar> <run> <rel_tar> <sample>

# compare
python3 start.py \
  --refFile <ref.root> \
  --targetFile <tar.root> \
  --refLabel <refLabel> \
  --targetLabel <targetLabel> \
  --FullPlots
```

---

## 10. Final note

The **manual workflow** is the recommended and most stable approach.  
`helper.py` is provided as a convenience tool but is **not required** for normal operation.
