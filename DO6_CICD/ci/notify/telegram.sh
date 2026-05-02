#!/usr/bin/env bash
set -euo pipefail

: "${TG_RELAY_URL:?TG_RELAY_URL is not set}"

STATUS="${1:-unknown}"     # success|failed
SCOPE="${2:-CI}"           # CI|CD
EXTRA_TEXT="${3:-}"

PROJECT="${CI_PROJECT_PATH:-unknown}"
BRANCH="${CI_COMMIT_REF_NAME:-unknown}"
PIPELINE_URL="${CI_PIPELINE_URL:-}"
JOB_URL="${CI_JOB_URL:-}"
COMMIT_SHA="${CI_COMMIT_SHORT_SHA:-}"

TEXT="[$SCOPE] status: ${STATUS}
project: ${PROJECT}
branch: ${BRANCH}
commit: ${COMMIT_SHA}
pipeline: ${PIPELINE_URL}
job: ${JOB_URL}"

if [[ -n "$EXTRA_TEXT" ]]; then
  TEXT="${TEXT}
${EXTRA_TEXT}"
fi

curl -sS --retry 3 --retry-delay 2 --retry-connrefused \
  -X POST "${TG_RELAY_URL}" \
  --data-urlencode "text=${TEXT}" > /dev/null || true