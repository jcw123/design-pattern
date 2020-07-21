##### scroll
> 使用scroll查询，可以防止深分页问题

```
POST /twitter/_search?scroll=1m
{
    "size": 100,
    "query": {
        "match" : {
            "title" : "elasticsearch"
        }
    }
}
```

```
POST /_search/scroll
{
    "scroll" : "1m",
    "scroll_id" : "DXF1ZXJ5QW5kRmV0Y2gBAAAAAAAAAD4WYm9laVYtZndUQlNsdDcwakFMNjU1QQ=="
}
```

```
GET /_search?scroll=1m
{
  "sort": [
    "_doc"
  ]
}
```

```
DELETE /_search/scroll
{
    "scroll_id" : "DXF1ZXJ5QW5kRmV0Y2gBAAAAAAAAAD4WYm9laVYtZndUQlNsdDcwakFMNjU1QQ=="
}
```

```
DELETE /_search/scroll
{
    "scroll_id" : [
      "DXF1ZXJ5QW5kRmV0Y2gBAAAAAAAAAD4WYm9laVYtZndUQlNsdDcwakFMNjU1QQ==",
      "DnF1ZXJ5VGhlbkZldGNoBQAAAAAAAAABFmtSWWRRWUJrU2o2ZExpSGJCVmQxYUEAAAAAAAAAAxZrUllkUVlCa1NqNmRMaUhiQlZkMWFBAAAAAAAAAAIWa1JZZFFZQmtTajZkTGlIYkJWZDFhQQAAAAAAAAAFFmtSWWRRWUJrU2o2ZExpSGJCVmQxYUEAAAAAAAAABBZrUllkUVlCa1NqNmRMaUhiQlZkMWFB"
    ]
}
```

```
DELETE /_search/scroll/_all
```

DXF1ZXJ5QW5kRmV0Y2gBAAAAAAAFMJ0WaUpYcUF6NU9UaW1ZV1B3aFNvUUhadw==
DXF1ZXJ5QW5kRmV0Y2gBAAAAAAAA4aEWeHlJVFA2WnNTbHlEaDJFZ1dlQ3U0QQ==

参考文档：
https://www.elastic.co/guide/en/elasticsearch/reference/6.3/search-request-scroll.html
