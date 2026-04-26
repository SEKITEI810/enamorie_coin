
# Enamorie Coin (ENAM)

Enamorie Coin is a cryptocurrency forked from Dogecoin. 
It features ultra-fast 30-second blocks, ultra-low fees, and a generous initial reward design.

---

## User Growth Features
| Feature | Dogecoin | Enamorie Coin | Effect / Benefit |
|------|----------|---------------|------|
| Block Time | 60 sec | **30 sec** | 2x faster confirmations → Improved UX |
| Minimum Fee | 0.01 DOGE | **0.001 ENAM** | 10x cheaper → Stimulates micro-tipping |
| Coinbase Maturity | 30 blocks | **10 blocks** | Miners can spend newly minted coins sooner |
| Initial Block Reward | Up to 1,000,000 DOGE | **Up to 50,000 ENAM** | Easier barrier to entry |
| Halving Interval | ~69 days | **~182 days** | Rewards last longer, retaining miners |
| Tail Emission | 10,000 DOGE forever | **500 ENAM forever** | Constant incentive for miners to keep mining |
| Max Supply | ~140 billion DOGE | **21 billion ENAM** | Balance of scarcity and adoption |

### Design Philosophy

1. **Ultra-fast blocks (30 seconds)** — Zero stress for Twitter tipping and everyday payments.
2. **Ultra-low fees (0.001 ENAM)** — Makes micro-tipping (like a 100-yen tip) practical.
3. **Slower halving schedule** — Prevents miners from abandoning the chain → Network stability → User trust.
4. **Permanent tail emission** — Mining incentives never disappear, ensuring a secure chain long-term.

---

## ⚙️ Technical Specifications

### Network
```text
Symbol:           ENAM
Max Supply:       21,000,000,000 ENAM (21 Billion)
Block Time:       30 seconds
Halving Interval: 525,600 blocks (~6 months)
Algorithm:        Scrypt + AuxPoW (Merged Mining Supported)
Mainnet Port:     33776
Testnet Port:     44776
AuxPoW Chain ID:  0x00E5 (229)
```

### Addresses
```text
Mainnet Pubkey:   Addresses starting with "E" (prefix byte: 33)
Mainnet Script:   Addresses starting with "e" (prefix byte: 28)
Testnet:          prefix byte 113 (0x71)
```

### Block Reward Schedule
```text
Phase 1 (Blocks 0-144,999): Random 1 to 50,000 ENAM (Dogecoin style)
Phase 2 (Blocks 145,000+):
  Era 0: 10,000 ENAM
  Era 1:  5,000 ENAM
  Era 2:  2,500 ENAM
  Era 3:  1,250 ENAM
  Era 4:    625 ENAM
  Era 5:    312 ENAM
  Era 6:    156 ENAM
  Era 7:     78 ENAM
  Era 8+:   500 ENAM (Permanent tail emission)
```

### Fees
```text
Recommended Minimum Fee: 0.001 ENAM/kB
Minimum Relay Fee:       0.0001 ENAM/kB
Dust Limit:              0.001 ENAM

Fee Tier Labels:
  Minimum    — Bare minimum
  Warm       — Warm
  Affection  — Affection
  Passion    — Passion
  Devoted    — Devoted
  Enamored   — In love
```

### Genesis Block
```text
Timestamp: 1745625600 (2025-04-26 00:00:00 UTC)
Message:   "Enamorie Coin - Love is the currency of tomorrow - 2025/04/26"
Reward:    2025 ENAM (Commemorating the year)
```

### Network Magic Bytes
```text
Mainnet: 0xe5 0xe4 0xe3 0xe2  (E N A M)
Testnet: 0xd5 0xd4 0xd3 0xd2
```

---

## 🔨 Build Instructions

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get install build-essential libtool autotools-dev automake \
  pkg-config libssl-dev libevent-dev bsdmainutils \
  libboost-system-dev libboost-filesystem-dev libboost-chrono-dev \
  libboost-program-options-dev libboost-test-dev libboost-thread-dev \
  libdb4.8-dev libdb4.8++-dev libminiupnpc-dev libzmq3-dev

# Build
./autogen.sh
./configure --with-gui=no  # CLI only (For GUI use --with-gui=qt5)
make -j$(nproc)

# Run
./src/enamorie-daemon -daemon
./src/enamorie-cli getinfo
```

---

## 📜 License

MIT License — The Enamorie Coin Core developers, based on Dogecoin Core and Bitcoin Core.
