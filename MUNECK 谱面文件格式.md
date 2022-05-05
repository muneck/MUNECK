# MUNECK 谱面文件格式

## 文件夹结构

```plain
StillAlive/
    meta.json
    chart5.json
    music.mp3
    illustration.jpg
```

其中 `meta.json` 包含谱面元信息 **（包括初始校准值）** ，`chartx.json` 为本曲难度为 $x$ 的谱面信息，`music.mp3`（其它格式也可）为音乐文件，`illustration.jpg`（其它格式也可）为曲绘图片。

## 元数据文件

### 文件格式

- `Name`：曲名
- `MusicFile`：音乐文件路径
- `IllustrationFile`：曲绘文件路径
- `Artist`：曲师
- `Illustrator`：画师
- `ChartOffset`：延迟，单位为秒，取值一切实数，值为负则**谱面先于音乐**该时间，值为正则**音乐先于谱面**该时间
- `Difficulties`：难度列表，**长度不限**
  - `DifficultyName`：难度名称，取值一切字符串
  - `Difficulty`：定数（难度的具体数值），取值 $[1, 20]$ 之间的整数
  - `Chart`：谱面文件路径
  - `ChartDesigner`：**该难度谱面**的谱师

### 示例

```json
{
    "Name": "Still Alive",
    "MusicFile": "music.mp3",
    "IllustrationFile": "illustration.jpg",
    "Artist": "Jonathan Coulton",
    "Illustrator": "Valve Corporation",
    "ChartOffset": -0.01,
    "Difficulties": [
        {
            "DifficultyName": "Easy",
            "Difficulty": 2,
            "Chart": "chart2.json",
            "ChartDesigner": "A very GLaD MUNECK team"
        }
    ]
}
```

## 谱面文件

### 文件格式

- `NoteNum`：物量，算分用

- `NoteList`：所有 note 的列表
  
  - `Type`：键型，取值 `flick`、`hold` 和 `avoid`，不区分大小写
  
  - `Rail`：轨道，取值 $[-2, 2]$ 之间的整数
  
  - `Length`：持续长度，仅会在键型为 `hold` 和 `avoid` 时读取，取值一切非负实数
  
  - `StartTime`：**音符碰到 receiver** 的时间，单位为秒
  
  - `DelayTime`：音符在 `StartTime` 之前多长时间出现，可近似为下落速度
    
    > 注：实际编程中，**音符应该在 `StartTime - DelayTime + DefaultOffset`** 时刻生成，其中 `DefaultOffset = min{ NoteList[i].StartTime - NoteList[i].DelayTime } (i = 0, 1, ..., NoteNum - 1)`，用来解决负数 tick 问题
    
    > 注2：`BP_notes_controller` 的 `current_tick` 是从 `max{0，DefaultOffset}` 开始累加的，而歌曲的播放时间永远是`current_tick=0`
    
    ### 示例

```json
{
    "Length": 10,
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
