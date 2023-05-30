#%%
from msedge.selenium_tools import Edge, EdgeOptions
import os
import requests
from urllib.parse import urljoin
from bs4 import BeautifulSoup
import shutil
import json
import time


## 在当前窗口中打开新标签页
#driver.execute_script("window.open('%s');" % url)
## 切换到新标签页
#driver.switch_to.window(driver.window_handles[-1])
import re
def cleanFilename(filename):
    # 将空格和斜杠替换成下划线
    filename = re.sub(r'[ /\\]', '_', filename)
    # 将冒号、星号、问号、双引号、小于号、大于号、竖线替换为空字符串
    filename = re.sub(r'[:*?"<>|]', '', filename)
    return filename

siteUrl = "http://manhua.ikukudm.com"
#%%
def getOneList(url:str, driver:Edge):
    driver.get(url)
    time.sleep(0.2)
    html = driver.execute_script("return document.documentElement.outerHTML;")
    soup = BeautifulSoup(html, 'html.parser')
    comicMain = soup.select('#comicmain')[0]
    comicList = comicMain.select('dd')

    comicInfos = []
    for comicOne in comicList:
        imgElement = comicOne.find('img')
        thumbnailUrl = imgElement.attrs['src']
        if not thumbnailUrl.startswith('http'):
            thumbnailUrl = urljoin('http://img.ikukudm.com/', thumbnailUrl)
        aLinks = comicOne.findAll('a')
        comicName = aLinks[-1].text
        #if comicName.find('/') != -1:
        #    comicName = comicName.replace('/', '_')
        #if comicName.find('\\') != -1:
        #    comicName = comicName.replace('\\', '_')
        comicName = cleanFilename(comicName)
        coimcLink = urljoin(siteUrl, aLinks[-1].get('href'))
        comicInfo = {"name": comicName, "thumbnailUrl": thumbnailUrl, "link": coimcLink}
        comicInfos.append(comicInfo)


    #%% 下载图片，并且保存数据在对应的目录
    listName = os.path.split(listUrl)[-1]
    dirName = os.path.join('data', listName)
    if os.path.exists(dirName):
        shutil.rmtree(dirName)
        os.mkdir(dirName)
    else:
        os.mkdir(dirName)
    fp = open(os.path.join(dirName, 'comics.json'), 'w', encoding='utf-8')
    json.dump(comicInfos, fp, indent=4, ensure_ascii=False)
    fp.close()
    for comic in comicInfos:
        imgName = os.path.join(dirName, comic['name'] + os.path.splitext(comic['thumbnailUrl'])[-1])
        try:
            response = requests.get(comic['thumbnailUrl'])
            with open(imgName, 'wb') as f:
                f.write(response.content)
        except:
            with open(os.path.join(dirName,'error.txt'), 'a') as ef:
                ef.write('FAILED to get: %s\t%s\n' % (comic['name'], comic['thumbnailUrl']))
    return


if __name__ == "__main__":
    # 初始化Edge选项
    options = EdgeOptions()
    options.use_chromium = True
    options.add_argument("--remote-debugging-port=9222")
    options.add_argument("--user-data-dir=S:\\EdgeGrabData")
    options.add_argument("--profile-directory=Default")


    # 创建Edge驱动对象，并指定要连接的已经运行的Edge进程ID
    driver = Edge(options=options, executable_path="msedgedriver.exe", port=9515, capabilities={"ms:edgeOptions": {"debuggerAddress": "localhost:9222"}})

    for num in range(120, 0, -1):
        listUrl = "/comictype/3_%d.htm" % num
        url = urljoin(siteUrl, listUrl)

        getOneList(url, driver=driver)
        print('done: url=%s' % url)

    #%% 完全退出所有窗口
    driver.quit()





#from selenium import webdriver
#from selenium.webdriver.edge.service import Service
#from selenium.webdriver.edge.options import Options
#
#edgeService = Service("msedgedriver.exe")
## 创建Edge浏览器选项对象
#edgeOptions = Options()
## 设置Edge浏览器启动时默认显示的页面大小
##edgeOptions.add_argument("window-size=1280,720")
## 禁用Edge浏览器的弹出窗口拦截器
## edgeOptions.set_capability("unhandledPromptBehavior", "accept")
#edgeOptions.add_argument(r'user-data-dir="S:\EdgeGrabData"')
#edgeOptions.add_argument(r'--profile-directory=grab')
#
## 创建Edge浏览器对象
#driver = webdriver.Edge(service=edgeService, options=edgeOptions)
## driver = webdriver.Edge(options=edgeOptions)
#
#
##%% 打开网站
#driver.get("http://manhua.ikukudm.com/comictype/3_175.htm")
#
#
##%% 退出
## driver.quit()
#
