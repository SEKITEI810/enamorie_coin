# 💕 Enamorie Coin (ENAM)

> *"Love is the currency of tomorrow"*

Enamorie Coin は Dogecoin をベースにフォークした、**コミュニティ・チップ文化**に特化した暗号通貨です。
高速な30秒ブロック・超低手数料・寛大な初期報酬設計により、ユーザーが自然に増える構造を持っています。

---

## 🌸 ユーザーが増える設計 (User Growth Features)

| 項目 | Dogecoin | Enamorie Coin | 効果 |
|------|----------|---------------|------|
| ブロック時間 | 60秒 | **30秒** | 確認が2倍速い → UX向上 |
| 最低手数料 | 0.01 DOGE | **0.001 ENAM** | 10倍安い → マイクロチップが活発化 |
| コインベース満期 | 30ブロック | **10ブロック** | マイナーがすぐ使える |
| 初期ブロック報酬 | 最大100万 DOGE | **最大5万 ENAM** | 参入しやすい |
| 半減期 | 約69日 | **約182日** | 報酬が長続きし採掘者が定着 |
| テール報酬 | 10,000 DOGE永久 | **500 ENAM永久** | マイナーが採掘し続ける動機 |
| 最大供給量 | 約1400億 DOGE | **210億 ENAM** | 希少性と普及のバランス |

### 設計思想

1. **超高速ブロック (30秒)** — Twitterチップや決済でストレスゼロ
2. **超低手数料 (0.001 ENAM)** — 100円のチップも現実的に
3. **愛テーマ** — "Enamorie" = 恋愛・魅了。心理的に親しみやすいブランド
4. **ゆっくりした半減期** — 採掘者が逃げない → ネットワーク安定 → ユーザー信頼
5. **永久テール報酬** — 採掘インセンティブが消えず、長期的に安全なチェーン

---

## ⚙️ 技術仕様 (Technical Specifications)

### ネットワーク
```
シンボル:         ENAM
最大供給量:        21,000,000,000 ENAM (210億)
ブロック時間:      30秒
半減期:           525,600 ブロック (~6ヶ月)
アルゴリズム:      Scrypt + AuxPoW (マージマイニング対応)
メインネットポート: 33776
テストネットポート: 44776
AuxPoW Chain ID:  0x00E5 (229)
```

### アドレス
```
Mainnet Pubkey:   "E" で始まるアドレス (prefix byte: 33)
Mainnet Script:   "e" で始まるアドレス (prefix byte: 28)
Testnet:          prefix byte 113 (0x71)
```

### ブロック報酬スケジュール
```
フェーズ1 (ブロック 0-144,999):    ランダム 1〜50,000 ENAM (Dogecoin スタイル)
フェーズ2 (ブロック 145,000+):
  Era 0: 10,000 ENAM
  Era 1:  5,000 ENAM
  Era 2:  2,500 ENAM
  Era 3:  1,250 ENAM
  Era 4:    625 ENAM
  Era 5:    312 ENAM
  Era 6:    156 ENAM
  Era 7:     78 ENAM
  Era 8+:   500 ENAM (永久テール報酬)
```

### 手数料
```
最低推奨手数料:    0.001 ENAM/kB
リレー最低手数料:  0.0001 ENAM/kB
ダスト制限:        0.001 ENAM

手数料ラベル (Fee Tier Labels):
  Minimum    — 最低限
  Warm       — 温かい
  Affection  — 愛情
  Passion    — 情熱
  Devoted    — 献身
  Enamored   — 恋愛中
```

### Genesis Block
```
タイムスタンプ: 1745625600 (2025-04-26 00:00:00 UTC)
メッセージ:    "Enamorie Coin - Love is the currency of tomorrow - 2025/04/26"
報酬:          2025 ENAM (年を記念)
```

### ネットワーク識別バイト
```
Mainnet: 0xe5 0xe4 0xe3 0xe2  (E N A M)
Testnet: 0xd5 0xd4 0xd3 0xd2
```

---

## 🚀 ローンチ前チェックリスト

### 必須作業

- [ ] **Genesis ブロックを採掘** して正しいハッシュを取得
- [ ] `src/chainparams.cpp` のハッシュアサーションを更新
- [ ] DNS シードノードを設置 (`seed.enamorie.org` など)
- [ ] `src/chainparamsseeds.h` をクリア（Dogecoin のシードを削除）
- [ ] テストネットで動作確認
- [ ] ウォレット UI の残りの "Dogecoin" テキストを全置換

### 推奨作業

- [ ] ロゴ・アイコンを作成（💕ハートをモチーフに）
- [ ] ブロックエクスプローラーをセットアップ
- [ ] ウォレット配布パッケージをビルド
- [ ] コミュニティフォーラム (Discord/Reddit) 開設
- [ ] 取引所上場申請
- [ ] Faucet（蛇口）サービス設置 → 新規ユーザー獲得

---

## 🔨 ビルド方法

```bash
# 依存関係インストール (Ubuntu/Debian)
sudo apt-get install build-essential libtool autotools-dev automake \
  pkg-config libssl-dev libevent-dev bsdmainutils \
  libboost-system-dev libboost-filesystem-dev libboost-chrono-dev \
  libboost-program-options-dev libboost-test-dev libboost-thread-dev \
  libdb4.8-dev libdb4.8++-dev libminiupnpc-dev libzmq3-dev

# ビルド
./autogen.sh
./configure --with-gui=no  # CLIのみ (GUIは --with-gui=qt5)
make -j$(nproc)

# 実行
./src/enamorie-daemon -daemon
./src/enamorie-cli getinfo
```

---

## 📁 主な変更ファイル

| ファイル | 変更内容 |
|---------|---------|
| `src/enamorie.cpp` | ブロック報酬ロジック (旧 dogecoin.cpp) |
| `src/enamorie.h` | 関数宣言 |
| `src/enamorie-fees.cpp` | 手数料計算・愛テーマラベル |
| `src/enamorie-fees.h` | 手数料定数 |
| `src/chainparams.cpp` | ネットワークパラメータ全般 |
| `src/amount.cpp` | 通貨単位 "ENAM" |
| `src/amount.h` | MAX_MONEY = 210億 ENAM |
| `src/policy/policy.h` | 手数料 0.001 ENAM |

---

## 📜 ライセンス

MIT License — The Enamorie Coin Core developers, based on Dogecoin Core and Bitcoin Core.
