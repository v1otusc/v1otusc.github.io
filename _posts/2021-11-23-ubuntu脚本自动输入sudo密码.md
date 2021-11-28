---
layout: post
title: ubuntu脚本自动输入sudo密码
---

实测有效，哈哈

```sh
#!/bin/bash
sudo -S command_to_execute status<<EOF
#your password
EOF
```
