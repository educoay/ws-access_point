# Wireless Access Point [Node32s]

Source code of the access point for the wireless scoreboard project

## Default IP Address

```
192.168.1.1
```

## Default SSID

```
project-husky
```

## Default Password

```
abcdefghijk
```

## Available RESTful APIs

1. Change Password

```
http://<IP Address>/changepass?params=<new password>
```

2. Home Score

```
http://<IP Address>/home?params=<score arg>-<value arg>
```

3. Away Score

```
http://<IP Address>/away?params=<score-arg>-<value arg>
```

Score arguments:

- set - Set score value
- plus - Increase score with \<value arg>
- minus - Decrease score with \<value arg>

Value arguments: \<Any Integer>
