const puppeteer = require('puppeteer');
const RE_FOLLOWERS_SHORT = /\d+(?:\.\d+[MK]|,\d+|[MK])?/;

class ParseError extends Error {}

async function getTwitterFollowers(handles) {
  const browser = await puppeteer.launch({ headless: true});
  const page = await browser.newPage();
  await page.setUserAgent('Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Safari/537.36')
  await page.setViewport({width: 3840, height: 2160});


  async function isElementVisible(selector) {
    const visible = await page.evaluate((selector) => {
      const e = document.querySelector(selector);
      if (e) return !!e.offsetParent;
    }, selector);
    return visible;
  }

  async function getFollowersElement(handle) {
    await page.goto(`https://twitter.com/${handle}`);
    await page.waitForSelector('a[href*="followers"]', { visible: true, timeout: 10000});
    return 'a[href*="followers"]'; // This is the selector for the followers element
  }

  async function extractShortNumFollowers(selector) {
    const text = await page.$eval(selector, el => el.textContent);
    console.log('Elemento Texto Inicial: ', text);
    const match = RE_FOLLOWERS_SHORT.exec(text);
    console.log('Retorno do Regex: ', match[0]);
    if (!match) throw new ParseError('Number of followers not found in the element');
    return match[0];
  }

  async function extractNumFollowers(selector, shortNum) {
    if (shortNum.endsWith('K') || shortNum.endsWith('M')) {
        console.log('Extraindo K ou M, e trocando o . por , para encontrar a entrada no Elemento')
      shortNum = shortNum.slice(0, -1).replace('.', ',');
      console.log('Numero apos troca: ', shortNum)
    } else {
      return parseInt(shortNum.replace(',', ''), 10);
    }
    await page.hover(selector);
    const textsBeforeHover = await page.evaluate(() => {
        const texts = Array.from(document.querySelectorAll('span')).map(el => el.textContent);
        return texts;
      });
      const uniqueTextsBeforeHover = Array.from(new Set(textsBeforeHover)).slice(0, 5);
      console.log('Elementos antes do hover:', uniqueTextsBeforeHover);
    await page.evaluate(selector => {
        const element = document.querySelector(selector);
        if (element) {
          element.dispatchEvent(new MouseEvent('mouseover', {bubbles: true}));
        }
      }, selector);

    await page.evaluate(() => {
        return new Promise(resolve => {
          setTimeout(resolve, 1000); 
        });
      });
      const elementsTexts = await page.evaluate(() => {
        const texts = Array.from(document.querySelectorAll('span')).map(el => el.textContent);
        return texts;
      });
      const uniqueTexts = Array.from(new Set(elementsTexts)).slice(0, 5);
      console.log('Elementos Apos Hover: ', uniqueTexts)
    

    await page.evaluate(() => {
        const elements = Array.from(document.querySelectorAll('span')).map(el => el.textContent);
        console.log(JSON.stringify(elements)); 
      });

  const fullNumberText = await page.evaluate(shortNum => {
    const element = Array.from(document.querySelectorAll('span')).find(el => el.textContent.includes(shortNum));
    console.log('elemento: ', element)
    return element ? element.textContent : null;
    }, shortNum);
    
    console.log('Numero completo pre-processamento: ', fullNumberText)
    
    const fullNumber = parseInt(fullNumberText.replace(/,/g, ''), 10)
    console.log('Numero pos-processamento: ', fullNumber)
    return fullNumber;
 }

  const results = [];
  for (let handle of handles) {
    console.log(`Processando: ${handle}`);
    try {
      const selector = await getFollowersElement(handle);
      const num = await extractShortNumFollowers(selector);
      const isVisible = await isElementVisible(selector);
      if (!isVisible) {
        throw new Error("Followers element not visible");
      }
      
      const realNum = await extractNumFollowers(selector, num);
      
      results.push({ handle, followers: realNum });
    } catch (error) {
      console.log(`Error processing ${handle}: ${error}`);
    }
  }

  await browser.close();
  return results;
}


(async () => {
    
  const handles =['animejujutsu']
  const data = await getTwitterFollowers(handles);
  
  console.log('Dados finais: ', data);
})();