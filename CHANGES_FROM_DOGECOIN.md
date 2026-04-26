# Dogecoin → Enamorie Coin 変更サマリー

## 識別子の変更

| 変更前 (Dogecoin) | 変更後 (Enamorie Coin) |
|------------------|-----------------------|
| `dogecoin` | `enamorie` |
| `DOGE` | `ENAM` |
| `koinu` (最小単位) | `enamo` (最小単位) |
| `GetDogecoinBlockSubsidy()` | `GetEnamorieBlockSubsidy()` |
| `CalculateDogecoinNextWorkRequired()` | `CalculateEnamorieNextWorkRequired()` |
| `GetDogecoinFeeRate()` | `GetEnamorieFeeRate()` |
| `GetDogecoinMinRelayFee()` | `GetEnamorieMinRelayFee()` |
| `dogecoin.cpp/.h` | `enamorie.cpp/.h` |
| `dogecoin-fees.cpp/.h` | `enamorie-fees.cpp/.h` |

## パラメータ変更

| パラメータ | Dogecoin | Enamorie Coin | 変更理由 |
|----------|----------|---------------|---------|
| ブロック時間 | 60秒 | **30秒** | 高速確認でUX向上 |
| 最低手数料 | 0.01 DOGE | **0.001 ENAM** | マイクロチップ促進 |
| コインベース満期 | 30ブロック | **10ブロック** | マイナーUX向上 |
| 半減期 | 100,000ブロック | **525,600ブロック** | ~6ヶ月、報酬の安定 |
| 初期最大報酬 | 100万 DOGE | **5万 ENAM** | 参入しやすい供給 |
| テール報酬 | 10,000 DOGE | **500 ENAM** | 永久採掘インセンティブ |
| 最大供給量 | ~1,400億 DOGE | **210億 ENAM** | 希少性と普及のバランス |
| デフォルトポート | 22556 | **33776** | ネットワーク衝突回避 |
| AuxPoW Chain ID | 0x0062 (98) | **0x00E5 (229)** | 一意識別 |
| アドレスプレフィックス | 'D' (30) | **'E' (33)** | ブランド識別 |
| メッセージバイト | 0xc0c0c0c0 | **0xe5e4e3e2** | ENAM の頭文字 |
| Genesis タイムスタンプ | 2013-12-06 | **2025-04-26** | Enamorie ローンチ日 |
| Genesis 報酬 | 88 DOGE | **2025 ENAM** | 年号記念 |

## 新規ファイル

- `src/enamorie.cpp` — ブロック報酬・PoW 計算 (dogecoin.cpp から改変)
- `src/enamorie.h` — 関数宣言
- `src/enamorie-fees.cpp` — 手数料計算、愛テーマの手数料ラベル
- `src/enamorie-fees.h` — 手数料定数・Enum
- `README.md` — プロジェクト概要
- `LAUNCH_GUIDE.md` — ローンチ手順・ユーザー獲得戦略
- `CHANGES_FROM_DOGECOIN.md` — 本ファイル

## 削除・クリア

- `src/chainparamsseeds.h` — Dogecoin のシードノードをクリア (要再設定)
- `checkpoints` — Dogecoin のチェックポイントをクリア (再採掘後に追加)
