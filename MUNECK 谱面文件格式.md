## 文件格式

- `NoteNum`：物量，算分用
- `NoteList`：所有 note 的列表
  - `Type`：键型，取值 `flick`、`hold` 和 `avoid`，不区分大小写
  - `Rail`：轨道，取值 $[-2, 2]$ 之间的整数
  - `Length`：持续长度，仅会在键型为 `hold` 和 `avoid` 时读取，取值一切非负实数
  - `StartTime`：**音符碰到 receiver** 的时间，单位为秒
  - `DelayTime`：音符在 `StartTime` 之前多长时间出现，可近似为下落速度
    注：实际编程中，**音符应该在 `StartTime - DelayTime + DefaultOffset`** 时刻生成，其中 `DefaultOffset = min{ NoteList[i].StartTime - NoteList[i].DelayTime } (i = 0, 1, ..., NoteNum - 1)`，用来解决负数 tick 问题

## 示例

```json
{
    "NoteNum": 3,
    "NoteList": [
        {
            "Type": "flick",
            "Rail": -2,
            "Length": 0.0,
            "StartTime": 1.0,
            "DelayTime": 2.0
        },
        {
            "Type": "hold",
            "Rail": -1,
            "Length": 1.0,
            "StartTime": 2.0,
            "DelayTime": 4.0
        },
        {
            "Type": "avoid",
            "Rail": 0,
            "Length": 1.0,
            "StartTime": 10.0,
            "DelayTime": 5.0
        }
    ]
}
```
