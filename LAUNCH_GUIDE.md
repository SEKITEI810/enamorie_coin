# 🚀 Enamorie Coin ローンチガイド

## Step 1: Genesis ブロックの採掘

Genesis ブロックは全ての PoW コインで手動採掘が必要です。

### 1-1. ビルド (regtest モード)

```bash
./autogen.sh && ./configure --with-gui=no && make -j$(nproc)
```

### 1-2. Regtest でジェネシス採掘スクリプト

```python
#!/usr/bin/env python3
# mine_genesis.py
import hashlib, struct, time

def sha256d(data):
    return hashlib.sha256(hashlib.sha256(data).digest()).digest()

def mine_genesis(timestamp, bits, nonce_start=0):
    target = (bits & 0xffffff) * (2 ** (8 * ((bits >> 24) - 3)))
    nonce = nonce_start
    while True:
        header = struct.pack('<I', 1)  # version
        header += b'\x00' * 32        # prevhash
        # merkle root (compute from genesis tx)
        header += struct.pack('<I', timestamp)
        header += struct.pack('<I', bits)
        header += struct.pack('<I', nonce)
        hash_val = int.from_bytes(sha256d(header), 'little')
        if hash_val < target:
            print(f"Nonce: {nonce}")
            print(f"Hash: {sha256d(header)[::-1].hex()}")
            break
        nonce += 1
        if nonce % 1000000 == 0:
            print(f"Trying nonce {nonce}...")

mine_genesis(1745625600, 0x1e0ffff0)
```

### 1-3. ハッシュを chainparams.cpp に更新

採掘後、以下のコメントアウト部分を実際のハッシュで置換:

```cpp
// src/chainparams.cpp の assert 部分を更新
assert(consensus.hashGenesisBlock == uint256S("0x<YOUR_GENESIS_HASH>"));
assert(genesis.hashMerkleRoot == uint256S("0x<YOUR_MERKLE_ROOT>"));
```

---

## Step 2: DNS シードノードの設置

### 2-1. VPS にフルノードをインストール

```bash
# Ubuntu 22.04 LTS 推奨
sudo apt-get install -y enamorie-daemon
enamorie-daemon -daemon -datadir=/var/lib/enamorie
```

### 2-2. DNS エントリ設定

```
seed.enamorie.org  →  <VPS IP>
seed2.enamorie.org →  <別のVPS IP>
```

### 2-3. chainparams.cpp のシードを有効化

```cpp
// コメントを外す
vSeeds.push_back(CDNSSeedData("enamorie.org", "seed.enamorie.org", true));
vSeeds.push_back(CDNSSeedData("enamorie.org", "seed2.enamorie.org"));
```

---

## Step 3: ユーザー獲得戦略

### 🎁 Faucet (蛇口) 設置 — 最重要

新規ユーザーは「まずコインをもらえる」体験が必要。

```
推奨: 毎日 10〜100 ENAM を無料配布
条件: アドレスまたは Twitter アカウント認証
```

**推奨 Faucet サービス:**
- FaucetPay.io で ENAM を追加申請
- 独自 Faucet: https://github.com/nicehash/faucet (参考実装)

### 📱 ウォレットアプリ

1. **Enamorie Web Wallet** — まず Web ウォレットをリリース (ブラウザで使える)
2. **Android/iOS** — Coinomi や Trust Wallet への追加申請

### 💬 コミュニティ施策

| チャンネル | 目的 | 初期施策 |
|-----------|------|---------|
| Discord | メインコミュニティ | 入会でENAM配布 |
| Twitter/X | 情報拡散 | チップbot (#ENAMtip) |
| Reddit r/EnamorieCoin | 議論 | ミームコンテスト |
| Telegram | アナウンス | ニュース配信 |

### 🎮 チップBot

Twitter/Discord でのチップが普及するとユーザー増加が加速。

```
使い方例:
  @ENAMtipbot tip @username 100 ENAM
```

**推奨実装:** Dogecoin の dogetipbot をフォーク

### 📊 取引所上場ロードマップ

```
Phase 1 (ローンチ): DEX (分散型) — 審査不要
  → ChangeNOW, SimpleSwap に申請

Phase 2 (1ヶ月後): 小規模 CEX
  → CoinEx, MEXC に申請

Phase 3 (3ヶ月後): 中規模 CEX
  → Gate.io, KuCoin に申請
```

---

## Step 4: マイニングプール

AuxPoW に対応しているため、Dogecoin マイニングプールと**マージマイニング**が可能。

```
マージマイニング対象プール:
  - Prohashing.com
  - Multipool.us

設定例 (mining.conf):
  algo=scrypt
  auxpow=1
  chainid=229  # ENAM の Chain ID
```

---

## 🎯 6ヶ月 KPI 目標

| 指標 | 1ヶ月 | 3ヶ月 | 6ヶ月 |
|------|-------|-------|-------|
| ウォレット数 | 1,000 | 10,000 | 50,000 |
| 日次トランザクション | 500 | 5,000 | 20,000 |
| マイナー数 | 10 | 50 | 200 |
| 取引所数 | 1 DEX | 3 | 8 |
| Discord メンバー | 500 | 3,000 | 15,000 |

