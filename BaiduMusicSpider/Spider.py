#!/usr/bin/python
import re
import cookielib
import urllib
import urllib2

# build cookies jar
cj = cookielib.CookieJar()
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
urllib2.install_opener(opener)

# get cookie
MainUrl = "http://www.baidu.com/"
res = urllib2.urlopen(MainUrl)
for index, cookie in enumerate(cj):
    print '[',index,']',cookie

# get tooken
getTokenUrl = "https://passport.baidu.com/v2/api/?getapi&class=login&tpl=mn&tangram=true"
res = urllib2.urlopen(getTokenUrl)
Html = res.read()
tokenStr = "bdPass.api.params.login_token='(.*?)';"
tokenObj = re.compile(tokenStr,re.DOTALL)
matchObj = tokenObj.findall(Html)
for index, cookie in enumerate(cj):
    print '[',index, ']',cookie;
if matchObj:
    token = matchObj[0]
    print matchObj[0]

# Login Baidu
LoginUrl = "https://passport.baidu.com/v2/api/?login"
postDict = {
        'charset':"utf-8",
        'token':token,
        'isPhone':"false",
        'index':"0",
        'staticpage':"https://passport.baidu.com/static/passpc-account/html/v3Jump.html",
        'logintype':"basicLogin",
        'tpl':"mn",
        'callback':"parent.bd__pcbs__b0pp2q",
        'username':"250831497@qq.com",
        'password':"220496",
        'mem_pass':"on",
        }
postData = urllib.urlencode(postDict);
print postData
req = urllib2.Request(LoginUrl,postData)
req.add_header('Content-Type', "application/x-www-form-urlencoded")
res = urllib2.urlopen(req)

# handle the baidu music web
Html = res.read()
print Html
for index, cookie in enumerate(cj):
    print '[',index, ']',cookie;
urlStr = "encodeURI\('(.*?)'\);"
urlObj = re.compile(urlStr,re.DOTALL)
matchUrl = urlObj.findall(Html)
if matchUrl:
    returnUrl = matchUrl[0]
#req = urllib2.Request(returnUrl)
#res = urllib2.urlopen(req)
#print res.read()
songUrl = "http://music.baidu.com/song/120948904/download"
req = urllib2.Request(songUrl)
res = urllib2.urlopen(req)
print res.read()
# TODO: get the download link
