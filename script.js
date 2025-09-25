// Run instructions:
// - Open directly in browser: double-click f:\Bao_Mat\index.html
// - Or serve the folder and browse localhost:
//   * Python 3:  cd /d f:\Bao_Mat && py -3 -m http.server 8000
//                 (or: python -m http.server 8000)
//   * Node (http-server): cd /d f:\Bao_Mat && npx http-server -p 8000
//   * Live reload: cd /d f:\Bao_Mat && npx live-server
//   Then open: http://localhost:8000
// - To run C++ (if present): g++ f:\Bao_Mat\classical_ciphers.cpp -O2 -std=c++17 -o f:\Bao_Mat\classical_ciphers.exe
//                         && f:\Bao_Mat\classical_ciphers.exe

function sanitize(s){
  return s.toUpperCase().replace(/[^A-Z]/g,'');
}
function mod26(x){ x%=26; if(x<0) x+=26; return x; }

// Caesar
function caesar_encrypt(pt,k){
  k = ((Number(k)||0)%26+26)%26;
  return sanitize(pt).split('').map(c=> String.fromCharCode(65 + (c.charCodeAt(0)-65 + k)%26)).join('');
}
function caesar_decrypt(ct,k){ return caesar_encrypt(ct, 26 - (Number(k)%26)); }

// Affine
function egcd(a,b){ if(b===0) return {g:a,x:1,y:0}; let r=egcd(b,a%b); return {g:r.g, x:r.y, y: r.x - Math.floor(a/b)*r.y}; }
function modinv(a,m){ let r=egcd(a,m); if(r.g!==1) return null; let inv = r.x % m; if(inv<0) inv+=m; return inv; }
function affine_encrypt(pt,a,b){
  a = Number(a); b = Number(b);
  return sanitize(pt).split('').map(c=>{
    return String.fromCharCode(65 + mod26(a*(c.charCodeAt(0)-65) + b));
  }).join('');
}
function affine_decrypt(ct,a,b){
  a = Number(a); b = Number(b);
  let ai = modinv(a,26); if(ai===null) return "Invalid a (no inverse)";
  return sanitize(ct).split('').map(c=> String.fromCharCode(65 + mod26(ai*(c.charCodeAt(0)-65 - b)))).join('');
}

// Columnar transposition (key word)
function keyOrder(key){
  let arr = key.split('').map((c,i)=>({c,i})).sort((x,y)=>(x.c===y.c? x.i-y.i: x.c<y.c?-1:1));
  let order = Array(key.length);
  arr.forEach((v,i)=> order[v.i]=i);
  return order;
}
function columnar_encrypt(pt,key){
  let s = sanitize(pt);
  let cols = key.length;
  let rows = Math.ceil(s.length/cols);
  while(s.length < rows*cols) s += 'X';
  let order = keyOrder(key);
  let out = '';
  for(let rank=0; rank<cols; rank++){
    for(let c=0;c<cols;c++) if(order[c]===rank){
      for(let r=0;r<rows;r++) out += s[r*cols + c];
      break;
    }
  }
  return out;
}
function columnar_decrypt(ct,key){
  let s = sanitize(ct);
  let cols = key.length;
  let rows = Math.ceil(s.length/cols);
  let order = keyOrder(key);
  let colsArr = Array(cols).fill('').map(()=>Array(rows).fill(''));
  let pos=0;
  for(let rank=0; rank<cols; rank++){
    for(let c=0;c<cols;c++) if(order[c]===rank){
      for(let r=0;r<rows;r++) colsArr[c][r]=s[pos++];
      break;
    }
  }
  let out='';
  for(let r=0;r<rows;r++) for(let c=0;c<cols;c++) out+=colsArr[c][r];
  return out;
}

// Vigenere
function vigenere_encrypt(pt,key){
  let s = sanitize(pt), k = sanitize(key);
  if(k.length===0) return s;
  return s.split('').map((ch,i)=> {
    let shift = k[i % k.length].charCodeAt(0)-65;
    return String.fromCharCode(65 + (ch.charCodeAt(0)-65 + shift)%26);
  }).join('');
}
function vigenere_decrypt(ct,key){
  let s = sanitize(ct), k = sanitize(key);
  if(k.length===0) return s;
  return s.split('').map((ch,i)=> {
    let shift = k[i % k.length].charCodeAt(0)-65;
    return String.fromCharCode(65 + mod26(ch.charCodeAt(0)-65 - shift));
  }).join('');
}

// Playfair
function buildPF(key){
  let k = sanitize(key).replace(/J/g,'I');
  let used = Array(26).fill(false); used['J'.charCodeAt(0)-65]=true;
  let seq = '';
  for(let ch of k) { if(!used[ch.charCodeAt(0)-65]){ used[ch.charCodeAt(0)-65]=true; seq+=ch; } }
  for(let c=65;c<=90;c++){ if(!used[c-65]){ seq += String.fromCharCode(c); } }
  let table = []; let pos = {};
  let p=0;
  for(let r=0;r<5;r++){ let row=[]; for(let c=0;c<5;c++){ row.push(seq[p]); pos[seq[p]] = [r,c]; p++; } table.push(row); }
  return {table,pos};
}
function pf_prepare(pt){
  let s = sanitize(pt).replace(/J/g,'I');
  let out=''; for(let i=0;i<s.length;){
    let a=s[i], b=(i+1<s.length? s[i+1]:'X');
    if(a===b){ out+=a; out+='X'; i++; } else { out+=a; out+=b; i+=2; }
  }
  if(out.length%2) out+='X';
  return out;
}
function playfair_encrypt(pt,key){
  let pf = buildPF(key);
  let s = pf_prepare(pt);
  let out='';
  for(let i=0;i<s.length;i+=2){
    let a=s[i], b=s[i+1];
    let pa = pf.pos[a], pb = pf.pos[b];
    if(pa[0]===pb[0]){
      out += pf.table[pa[0]][(pa[1]+1)%5];
      out += pf.table[pb[0]][(pb[1]+1)%5];
    } else if(pa[1]===pb[1]){
      out += pf.table[(pa[0]+1)%5][pa[1]];
      out += pf.table[(pb[0]+1)%5][pb[1]];
    } else {
      out += pf.table[pa[0]][pb[1]];
      out += pf.table[pb[0]][pa[1]];
    }
  }
  return out;
}
function playfair_decrypt(ct,key){
  let pf = buildPF(key);
  let s = sanitize(ct);
  let out='';
  for(let i=0;i<s.length;i+=2){
    let a=s[i], b=s[i+1];
    let pa = pf.pos[a], pb = pf.pos[b];
    if(pa[0]===pb[0]){
      out += pf.table[pa[0]][(pa[1]+4)%5];
      out += pf.table[pb[0]][(pb[1]+4)%5];
    } else if(pa[1]===pb[1]){
      out += pf.table[(pa[0]+4)%5][pa[1]];
      out += pf.table[(pb[0]+4)%5][pb[1]];
    } else {
      out += pf.table[pa[0]][pb[1]];
      out += pf.table[pb[0]][pa[1]];
    }
  }
  return out;
}

// add: playfair debug helper (show table, prepared digraphs, ciphertext)
function playfair_debug_info(key, pt){
  const pf = buildPF(key);
  const prepared = pf_prepare(pt);
  const ct = playfair_encrypt(pt, key);
  // render table
  const tableLines = pf.table.map(r => r.join(' ')).join('\n');
  return {
    tableText: tableLines,
    prepared: prepared,
    ciphertext: ct
  };
}

// add: render visual Playfair demo (table, digraphs, ciphertext, decryption)
function renderPlayfairDemo(key, pt){
  const k = key && key.trim().length ? key : 'PLAYFAIR EXAMPLE';
  const p = pt && pt.trim().length ? pt : 'HIDE THE GOLD IN THE TREE STUMP';
  const info = playfair_debug_info(k, p);

  // ensure demo container exists
  let demo = document.getElementById('pf_demo_container');
  if(!demo){
    demo = document.createElement('div');
    demo.id = 'pf_demo_container';
    demo.style.marginTop = '10px';
    demo.style.padding = '10px';
    demo.style.border = '1px solid #ddd';
    demo.style.background = '#fafafa';
    demo.style.borderRadius = '6px';
    const hint = document.getElementById('usage_hint');
    if(hint && hint.parentNode) hint.parentNode.insertBefore(demo, hint.nextSibling);
    else document.body.appendChild(demo);
  }
  // build HTML
  demo.innerHTML = '';
  const title = document.createElement('div');
  title.style.fontWeight = '700';
  title.style.marginBottom = '6px';
  title.textContent = 'Playfair demo — key: ' + k;
  demo.appendChild(title);

  // table
  const tableWrap = document.createElement('div');
  tableWrap.style.marginBottom = '8px';
  const tableEl = document.createElement('table');
  tableEl.style.borderCollapse = 'collapse';
  tableEl.style.marginBottom = '6px';
  for(const row of info.tableText.split('\n')){
    const tr = document.createElement('tr');
    row.split(' ').forEach(cell=>{
      const td = document.createElement('td');
      td.textContent = cell;
      td.style.border = '1px solid #ccc';
      td.style.padding = '6px 8px';
      td.style.textAlign = 'center';
      td.style.fontFamily = 'monospace';
      tr.appendChild(td);
    });
    tableEl.appendChild(tr);
  }
  tableWrap.appendChild(tableEl);
  demo.appendChild(tableWrap);

  // prepared digraphs
  const preDiv = document.createElement('div');
  preDiv.style.marginBottom = '6px';
  preDiv.innerHTML = '<strong>Prepared digraphs:</strong><br>' + (info.prepared.match(/.{1,2}/g)||[]).join(' ');
  demo.appendChild(preDiv);

  // ciphertext + decryption check
  const ciphDiv = document.createElement('div');
  ciphDiv.style.marginBottom = '6px';
  ciphDiv.innerHTML = '<strong>Ciphertext:</strong><br>' + info.ciphertext;
  demo.appendChild(ciphDiv);

  const dec = playfair_decrypt(info.ciphertext, k);
  const decDiv = document.createElement('div');
  decDiv.innerHTML = '<strong>Decrypted back:</strong><br>' + dec;
  demo.appendChild(decDiv);

  // also set result field and leave inputs (so user can use)
  const resultEl = document.getElementById('result');
  if(resultEl) resultEl.value = info.ciphertext;
  const keyEl = document.getElementById('key');
  const textEl = document.getElementById('text');
  if(keyEl) keyEl.value = k;
  if(textEl) textEl.value = p;
}

// add: show usage hints and feedback in the UI
function setUsageHints(){
  // set placeholders
  const keyEl = document.getElementById('key');
  if(keyEl) keyEl.placeholder = 'Caesar: 3  |  Affine: 5 8  |  Columnar: ZEBRA  |  Vigenere: LEMON  |  Playfair: PLAYFAIR';

  const textEl = document.getElementById('text');
  if(textEl) textEl.placeholder = 'Enter plaintext for Encrypt, or ciphertext for Decrypt. Non-letters ignored.';

  // insert or update a small hint area above the result
  const resultEl = document.getElementById('result');
  if(resultEl){
    let hint = document.getElementById('usage_hint');
    if(!hint){
      hint = document.createElement('div');
      hint.id = 'usage_hint';
      hint.style.margin = '8px 0';
      hint.style.color = '#444';
      hint.style.fontSize = '0.9em';
      resultEl.parentNode.insertBefore(hint, resultEl);
    }
    hint.textContent = 'Tip: For Encrypt → put plaintext and click Encrypt. For Decrypt → put ciphertext and click Decrypt. Output is uppercase letters.';

    // add Playfair demo button (once)
    if(!document.getElementById('pf_demo_btn')){
      const btn = document.createElement('button');
      btn.id = 'pf_demo_btn';
      btn.type = 'button';
      btn.textContent = 'Playfair demo';
      btn.style.marginLeft = '8px';
      hint.appendChild(btn);
      btn.addEventListener('click', ()=>{
        const sampleKey = 'PLAYFAIR EXAMPLE';
        const samplePt = 'HIDE THE GOLD IN THE TREE STUMP';
        // fill inputs
        const keyEl = document.getElementById('key');
        const textEl = document.getElementById('text');
        if(keyEl) keyEl.value = sampleKey;
        if(textEl) textEl.value = samplePt;
        // compute debug info
        const info = playfair_debug_info(sampleKey, samplePt);
        // show debug in hint area (formatted)
        hint.innerText = '';
        const pre = document.createElement('pre');
        pre.style.background = '#f0f0f0';
        pre.style.padding = '8px';
        pre.style.borderRadius = '4px';
        pre.style.whiteSpace = 'pre-wrap';
        pre.textContent = 'Playfair table (5x5):\n' + info.tableText + '\n\nPrepared digraphs:\n' + info.prepared.match(/.{1,2}/g).join(' ') + '\n\nCiphertext:\n' + info.ciphertext;
        hint.appendChild(pre);
        // also set result field
        const resultEl = document.getElementById('result');
        if(resultEl) resultEl.value = info.ciphertext;
      });
    }
  }
}

// replace previous DOMContentLoaded block with robust initializer
function initUI(){
  const encBtn = document.getElementById('enc');
  const decBtn = document.getElementById('dec');
  const methodEl = document.getElementById('method');
  const keyEl = document.getElementById('key');
  const textEl = document.getElementById('text');
  const resultEl = document.getElementById('result');

  if(!encBtn || !decBtn || !methodEl || !keyEl || !textEl || !resultEl){
    console.error('UI elements missing', {encBtn, decBtn, methodEl, keyEl, textEl, resultEl});
    let err = document.getElementById('ui_error');
    if(!err){
      err = document.createElement('div');
      err.id = 'ui_error';
      err.style.color = 'red';
      err.style.padding = '8px';
      err.style.fontWeight = '600';
      err.style.background = '#ffecec';
      err.style.border = '1px solid #f5c2c2';
      err.style.margin = '8px';
      document.body.insertBefore(err, document.body.firstChild);
    }
    err.textContent = 'Lỗi: giao diện chưa tải đầy đủ hoặc thiếu phần tử. Mở DevTools (F12) để xem console.';
    return;
  }

  // remove prior error if any
  const prevErr = document.getElementById('ui_error');
  if(prevErr) prevErr.remove();

  // setup hints and UI
  setUsageHints();
  const hint = document.getElementById('usage_hint');

  encBtn.addEventListener('click', ()=>{
    const method = methodEl.value;
    const key = keyEl.value;
    const text = textEl.value;
    let out = '';
    if(method==='caesar') out = caesar_encrypt(text, key);
    else if(method==='affine'){ let parts = key.replace(/,/g,' ').trim().split(/\s+/); out = affine_encrypt(text, parts[0]||1, parts[1]||0); }
    else if(method==='columnar') out = columnar_encrypt(text, key||'KEY');
    else if(method==='vigenere') out = vigenere_encrypt(text, key);
    else if(method==='playfair') out = playfair_encrypt(text, key||'KEY');
    resultEl.value = out;
    if(hint) hint.textContent = 'Encrypted (input treated as plaintext). Use the ciphertext above to decrypt later.';
  });

  decBtn.addEventListener('click', ()=>{
    const method = methodEl.value;
    const key = keyEl.value;
    const text = textEl.value;
    let out = '';
    if(method==='caesar') out = caesar_decrypt(text, key);
    else if(method==='affine'){ let parts = key.replace(/,/g,' ').trim().split(/\s+/); out = affine_decrypt(text, parts[0]||1, parts[1]||0); }
    else if(method==='columnar') out = columnar_decrypt(text, key||'KEY');
    else if(method==='vigenere') out = vigenere_decrypt(text, key);
    else if(method==='playfair') out = playfair_decrypt(text, key||'KEY');
    resultEl.value = out;
    if(hint) hint.textContent = 'Decrypted (input treated as ciphertext). If result looks wrong, ensure you supplied the actual ciphertext produced by Encrypt.';
  });
}

// try initialize now and also on DOMContentLoaded (covers both load orders)
try { initUI(); } catch(e){ console.error('initUI error', e); }
document.addEventListener('DOMContentLoaded', ()=> { try { initUI(); } catch(e){ console.error('DOMContentLoaded initUI error', e); } });

// replace the existing Playfair demo button handler inside setUsageHints()
// with a call to renderPlayfairDemo(key,pt) so clicking shows the formatted demo.
// (If setUsageHints already created a pf_demo_btn, keep the button but update its handler)
(function ensurePfDemoBtn(){
  const existing = document.getElementById('pf_demo_btn');
  if(existing){
    existing.removeEventListener && existing.removeEventListener('click', ()=>{}); // no-op, safe
    existing.addEventListener('click', ()=>{
      const keyEl = document.getElementById('key');
      const textEl = document.getElementById('text');
      const sampleKey = (keyEl && keyEl.value.trim()) ? keyEl.value : 'PLAYFAIR EXAMPLE';
      const samplePt = (textEl && textEl.value.trim()) ? textEl.value : 'HIDE THE GOLD IN THE TREE STUMP';
      renderPlayfairDemo(sampleKey, samplePt);
    });
  }
})();