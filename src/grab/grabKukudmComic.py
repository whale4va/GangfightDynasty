import os
import json
from bs4 import BeautifulSoup
from msedge.selenium_tools import Edge, EdgeOptions
import os
import requests
from urllib.parse import urljoin
import argparse




if __name__ == "__main__":
    # 初始化Edge选项
    options = EdgeOptions()
    options.use_chromium = True
    options.add_argument("--remote-debugging-port=9222")
    options.add_argument("--user-data-dir=S:\\EdgeGrabData")
    options.add_argument("--profile-directory=Default")


    # 创建Edge驱动对象，并指定要连接的已经运行的Edge进程ID
    driver = Edge(options=options, executable_path="msedgedriver.exe", port=9515, capabilities={"ms:edgeOptions": {"debuggerAddress": "localhost:9222"}})


    pass
