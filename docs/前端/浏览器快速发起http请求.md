# 浏览器快速发起http请求

## 方式一
通过XMLHttpRequest请求
```js
const xhr = new XMLHttpRequest();
xhr.open('POST', "http://localhost:8082/test", true);
xhr.setRequestHeader('Content-Type', 'application/json');
// Define callback function
xhr.onload = function() {
  if (xhr.status === 200) {
    console.log(xhr.responseText);
  } else {
    console.error('Error:', xhr.status);
  }
};

// Send request
const data = JSON.stringify({ name: 'John', age: 30 });
xhr.send(data);
```

## 方式二
通过fetch方法进行请求
```js
fetch('http://localhost:8082/test', {
  method: 'POST',
  headers: {
    'Content-Type': 'application/json'
  },
  body: JSON.stringify({ name: 'John', age: 30 })
})
.then(response => {
  if (response.ok) {
    return response.json();
  } else {
    throw new Error('Network response was not ok');
  }
})
.then(data => console.log(data))
.catch(error => console.error('Error:', error));
```

## 参考文档
[fetch api说明](https://developer.mozilla.org/en-US/docs/Web/API/Window/fetch)