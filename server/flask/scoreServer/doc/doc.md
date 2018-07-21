FORMAT:1A

# Group Score

## スコアを登録するエンドポイント [/api/score{?usrname,score}]

### スコア登録 [POST]

#### 概要
* パラメータのusrnameとscoreをDBに保存する。
* usrname,scoreそれぞれ必須。
* scoreに文字列を入れた場合は登録されない。

+ Parameters
    + usrname: chino(string, required) - ユーザー名
    + score: 124 (number, required) - スコア

## ハイスコアTOP10を返すエンドポイント [/api/score/list]

### ハイスコアTOP10 [GET]

#### 概要
* DB内に保存されているハイスコアTOP10を降順で返す。
* レコードが10未満の場合はレコードの数だけ返す。

+ Response 200 (application/json)

    + Attributes (array)
        + (object)
            + usrname: chino(string, required)
            + score: 124 (number,required)