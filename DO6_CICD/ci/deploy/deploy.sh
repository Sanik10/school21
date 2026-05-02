#!/usr/bin/env bash
set -euo pipefail

PROD_HOST="192.168.56.3"
PROD_USER="albinosu"
SSH_KEY="/home/gitlab-runner/.ssh/do6_deploy_key"

test -f "$SSH_KEY"

test -f artifacts/bin/s21_cat
test -f artifacts/bin/s21_grep

scp -i "$SSH_KEY" -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null \
  artifacts/bin/s21_cat artifacts/bin/s21_grep \
  "$PROD_USER@$PROD_HOST:/tmp/"

ssh -i "$SSH_KEY" -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null \
  "$PROD_USER@$PROD_HOST" \
  "sudo install -m 0755 /tmp/s21_cat /usr/local/bin/s21_cat &&
   sudo install -m 0755 /tmp/s21_grep /usr/local/bin/s21_grep"
