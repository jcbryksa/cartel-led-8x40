/*
 * JCBLedMatrixMAX7219 - website.h
 *
 * Copyright 2020 - Juan C. Bryksa (jcbryksa@gmail.com)
 */
#ifndef WEBSITE_H
#define WEBSITE_H

const char PROGMEM web_part1[] = {
"<!DOCTYPE html>\n\
<html lang='en'>\n\
<head>\n\
    <meta charset='UTF-8'>\n\
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n\
    <meta http-equiv='X-UA-Compatible' content='ie=edge'>\n\
    <title>Cartel LED</title>\n\
    <script>\n\
        let messages = '"
};


const char PROGMEM web_part2[] = {
"';\n\
    </script>\n\
    <style>\n\
        body {\n\
            font-family: Arial, Helvetica, sans-serif;\n\
        }\n\
        select, textarea {\n\
            font-size: 14px;\n\
            padding: 2px 5px 2px 5px;\n\
            display:inline-block;\n\
            position:relative;\n\
            color:black;\n\
            border:1px solid #ccc;\n\
            border-radius: 5px;\n\
            min-width: 50px;\n\
        }\n\
        textarea {\n\
            min-width: 200px;\n\
            min-height: 80px;\n\
        }\n\
        td {\n\
            text-align: center;\n\
            border: solid rgb(139, 138, 138) 1px;\n\
            padding: 5px;\n\
        }\n\
        tr.selected {\n\
            background-color:dodgerblue;\n\
        }\n\
        button {\n\
            padding: 10px;\n\
            font-weight: bold;\n\
            color: white;\n\
            border-radius: 8px;\n\
            margin: 10px 2px 10px 2px;\n\
            cursor: pointer;\n\
        }\n\
        button.save{\n\
            background-color: green;\n\
        }\n\
        button.del{\n\
            background-color: red;\n\
        }\n\
        button.disabled{\n\
            background-color: gray;\n\
            cursor: auto;\n\
        }\n\
        button.add{\n\
            background-color: blue;\n\
        }\n\
        .loading {\n\
            background-color: lightblue;\n\
            border-radius: 4px;\n\
            color:white;\n\
            padding: 3px 20px 3px 20px;\n\
            visibility: hidden;\n\
        }\n\
        .header {\n\
            font-size: 16px;\n\
            font-weight: bold;\n\
        }\n\
        .orderLabel {\n\
            background-color: silver;\n\
            font-weight: bold;\n\
            font-size: 16px;\n\
            cursor: pointer;\n\
        }\n\
        .actionCell {\n\
            width: 30px;\n\
            color: red;\n\
            cursor: pointer;\n\
            font-weight: bold;\n\
        }\n\
    </style>\n\
</head>\n\
<body>\n\
    <h1>Mensajes del cartel</h1>\n\
    <hr>\n\
    <button class='save'>Guardar</button> <button class='add'>Agregar / Insertar</button> <button class='del'>Eliminar</button> <span class='loading'>. . .</span>\n\
    <table id='tblMessages' cellspacing='0' cellpadding='0'>\n\
        <tr class='header'><td>Orden</td><td>Texto</td><td>Efecto de Entrada</td><td>Efecto de Salida</td><td>Velocidad</td><td>Pausa</td><td style='color:red;'>Borrar</td></tr>\n\
    </table>\n\
    <button class='save'>Guardar</button> <button class='add'>Agregar / Insertar</button> <button class='del'>Eliminar</button> <span class='loading'>. . .</span>\n\
\n\
    <script>\n\
\n\
        const getById = (id) => document.getElementById(id);\n\
        const getByClass = (c) => document.getElementsByClassName(c);\n\
\n\
        const tbl = getById('tblMessages');\n\
\n\
        const deleteRow = (row) => {\n\
            if (confirm('Realmente desea eliminar este mensaje?')) {\n\
                saveEnable(true);\n\
                row.remove();\n\
                updRowIndex();\n\
                clearSelRow();\n\
            }\n\
        };\n\
\n\
        const clearSelRow = () => {\n\
            Array.from(tbl.getElementsByTagName('tr')).forEach((r) => {\n\
                r.classList.remove('selected');\n\
            });\n\
            delEnable(false);\n\
        };\n\
\n\
        const selRow = (selected) => {\n\
\n\
            const rows = Array.from(tbl.getElementsByTagName('tr'));\n\
            const l = selected.classList;\n\
\n\
            rows.forEach( (r) => {\n\
                if(r.rowIndex != selected.rowIndex)\n\
                    r.classList.remove('selected');\n\
            });\n\
\n\
            if( l.contains('selected') ) {\n\
                l.remove('selected');\n\
                delEnable(false);\n\
            }\n\
            else {\n\
                l.add('selected');\n\
                delEnable(true);\n\
            }\n\
\n\
        };\n\
\n\
        const updRowIndex = () => {\n\
\n\
            const rows = Array.from(tbl.getElementsByTagName('tr'));\n\
\n\
            for ( let i = 1 ; i < rows.length ; i++ ) {\n\
                let cols = rows[i].getElementsByTagName('td');\n\
\n\
                cols[0].innerHTML = i;\n\
\n\
                let span = cols[5].getElementsByTagName('span');\n\
                if ( rows.length > 2 ) {\n\
                    cols[6].innerHTML = '<span class=\\'actionCell\\' title=\\'Eliminar mensaje\\'>X</span>';\n\
                    cols[6].getElementsByTagName('span')[0].onclick = () =>deleteRow(rows[i]);\n\
                }\n\
                else if ( span.length )\n\
                    span[0].remove();\n\
\n\
                cols[0].onclick = () => selRow(rows[i]);\n\
\n\
            }\n\
\n\
        };\n\
\n\
        const saveEnable = (enable) => {\n\
            Array.from(document.getElementsByClassName('save')).forEach((e)=>{\n\
                if (enable) {\n\
                    e.disabled = false;\n\
                    e.classList.remove('disabled');\n\
                } else {\n\
                    e.disabled = true;\n\
                    e.classList.add('disabled');\n\
                }\n\
            });\n\
        };\n\
\n\
        const delEnable = (enable) => {\n\
            \n\
            Array.from(document.getElementsByClassName('del')).forEach((e)=>{\n\
                if (enable) {\n\
                    e.disabled = false;\n\
                    e.classList.remove('disabled');\n\
                } else {\n\
                    e.disabled = true;\n\
                    e.classList.add('disabled');\n\
                }\n\
            });\n\
        };\n\
\n\
        const loading = (l) => {\n\
            if (l) v = 'visible';\n\
            else  v = 'hidden';\n\
            Array.from(getByClass('loading')).forEach((e)=>{e.style.visibility = v});\n\
        };\n\
\n\
        const addRow = (p) => {\n\
\n\
            let tr = document.createElement('tr');\n\
            const effects = [\n\
                {v:'0', d:'No_effect'},\n\
                {v:'1', d:'Print'},\n\
                {v:'2', d:'Scroll_up'},\n\
                {v:'3', d:'Scroll_down'},\n\
                {v:'4', d:'Scroll_right'},\n\
                {v:'5', d:'Scroll_left'},\n\
                {v:'6', d:'Sprite'},\n\
                {v:'7', d:'Slice'},\n\
                {v:'8', d:'Mesh'},\n\
                {v:'9', d:'Fade'},\n\
                {v:'10',d:'Dissolve'},\n\
                {v:'11',d:'Blinds'},\n\
                {v:'12',d:'Random'},\n\
                {v:'13',d:'Wipe'},\n\
                {v:'14',d:'Wipe_cursor'},\n\
                {v:'15',d:'Scan_horiz'},\n\
                {v:'16',d:'Scan_horizx'},\n\
                {v:'17',d:'Scan_vert'},\n\
                {v:'18',d:'Scan_vertx'},\n\
                {v:'19',d:'Opening'},\n\
                {v:'20',d:'Opening_cursor'},\n\
                {v:'21',d:'Closing'},\n\
                {v:'22',d:'Closing_cursor'},\n\
                {v:'23',d:'Scroll_up_right'},\n\
                {v:'24',d:'Scroll_up_left'},\n\
                {v:'25',d:'Scroll_down_right'},\n\
                {v:'26',d:'Scroll_down_left'},\n\
                {v:'27',d:'Grow_up'},\n\
                {v:'28',d:'Grow_down'}\n\
            ];\n\
\n\
            const spedds = [\n\
                {v:'90',d:'1'},\n\
                {v:'85',d:'2'},\n\
                {v:'80',d:'3'},\n\
                {v:'75',d:'4'},\n\
                {v:'70',d:'5'},\n\
                {v:'65',d:'6'},\n\
                {v:'60',d:'7'},\n\
                {v:'55',d:'8'},\n\
                {v:'50',d:'9'},\n\
                {v:'45',d:'10'},\n\
                {v:'40',d:'11'},\n\
                {v:'35',d:'12'},\n\
                {v:'30',d:'13'},\n\
                {v:'25',d:'14'},\n\
                {v:'20',d:'15'},\n\
                {v:'15',d:'16'},\n\
                {v:'10',d:'17'},\n\
                {v:'5' ,d:'18'},\n\
                {v:'3' ,d:'19'},\n\
                {v:'1' ,d:'20'}\n\
            ];\n\
\n\
            const pauses = [\n\
                {v:'1'   ,d: '0'},\n\
                {v:'1000',d: '1'},\n\
                {v:'2000',d: '2'},\n\
                {v:'3000',d: '3'},\n\
                {v:'4000',d: '4'},\n\
                {v:'5000',d: '5'},\n\
                {v:'6000',d: '6'},\n\
                {v:'7000',d: '7'},\n\
                {v:'8000',d: '8'},\n\
                {v:'9000',d: '9'},\n\
                {v:'10000',d:'10'}\n\
            ];\n\
\n\
            let rowHtml =\n\
             '<td class=\\'orderLabel\\'><span>1</span></td> '\n\
            +'<td><textarea>(mensaje)</textarea></td> '\n\
            +'<td> '\n\
            +    '<select> ';\n\
\n\
            effects.forEach((e) => rowHtml += `<option value='${e.v}'>${e.d}</option>`)\n\
\n\
            rowHtml +=\n\
                 '</select> '\n\
            +'</td> '\n\
            +'<td> '\n\
            +    '<select> ';\n\
\n\
            effects.forEach((e) => rowHtml += `<option value='${e.v}'>${e.d}</option>`)\n\
\n\
            rowHtml +=\n\
                 '</select> '\n\
            +'</td> '\n\
            +'<td> '\n\
            +    '<select> ';\n\
\n\
            spedds.forEach((s) => rowHtml += `<option value='${s.v}'>${s.d}</option>`)\n\
\n\
            rowHtml +=\n\
                 '</select> '\n\
            +'</td> '\n\
            +'<td> '\n\
            +    '<select> ';\n\
\n\
            pauses.forEach((p) => rowHtml += `<option value='${p.v}'>${p.d}</option>`)\n\
\n\
            rowHtml +=\n\
                 '</select> '\n\
            +'</td> '\n\
            +'<td> </td>';\n\
\n\
            tr.innerHTML = rowHtml;\n\
            \n\
            const rowSelected = getByClass('selected');\n\
            if (rowSelected.length)\n\
                rowSelected[0].parentNode.insertBefore(tr, rowSelected[0].nextSibling);\n\
            else\n\
                tbl.appendChild(tr);\n\
\n\
            const get = (n) => tr.getElementsByTagName(n);\n\
\n\
            updRowIndex();\n\
\n\
            const t = get('textarea')[0];\n\
            const s = get('select');\n\
\n\
            if (p) {\n\
                t.value = p[0];\n\
                s[0].value   = p[1];\n\
                s[1].value   = p[2];\n\
                s[2].value   = p[3];\n\
                s[3].value   = p[4];\n\
            } else {\n\
                t.value = '-Mensaje-';\n\
                s[0].value   = 5;\n\
                s[1].value   = 5;\n\
                s[2].value   = 30;\n\
                s[3].value   = 1;\n\
                t.select();\n\
            }\n\
\n\
            Array.from(s).forEach((e)=>{\n\
                e.onchange = ()=>saveEnable(true);\n\
            });\n\
\n\
            t.onkeypress = ()=>saveEnable(true);\n\
            t.onchange = ()=>saveEnable(true);\n\
\n\
        };\n\
\n\
\n\
        const save = () => {\n\
\n\
            messages = '';\n\
\n\
            Array.from(tbl.getElementsByTagName('tr')).forEach((r)=>{\n\
\n\
                const get = (n) => r.getElementsByTagName(n);\n\
                const t = get('textarea')[0];\n\
                const s = get('select');\n\
\n\
                if ( r.className == 'header' )\n\
                    return;\n\
\n\
                messages += s[0].value +'`'+ s[1].value +'`1`'+ s[2].value +'`'+ s[3].value +'^'+ t.value +'~';\n\
\n\
            });\n\
\n\
            saveEnable(false);\n\
\n\
            let xhr = new XMLHttpRequest();\n\
\n\
            loading(true);\n\
\n\
            xhr.open('POST', 'http://192.168.4.1:8081/save');\n\
            xhr.onreadystatechange = ()=>{\n\
                if ( xhr.readyState > 3 && xhr.status == 200 ) {\n\
                    loading(false);//alert(xhr.responseText);\n\
                }\n\
            };\n\
            //xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest');\n\
            //xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');\n\
            xhr.send(messages);\n\
\n\
        };\n\
\n\
        document.addEventListener('DOMContentLoaded', function() {\n\
\n\
            Array.from(getByClass('add')).forEach((e)=>{\n\
                e.onclick = ()=>{\n\
                    addRow();\n\
                    saveEnable(true);\n\
                }\n\
            });\n\
\n\
            Array.from(getByClass('save')).forEach((e)=>{\n\
                e.onclick = ()=>save();\n\
            });\n\
\n\
            Array.from(getByClass('del')).forEach((e)=>{\n\
                e.onclick = ()=>deleteRow(getByClass('selected')[0]);\n\
            });\n\
\n\
            saveEnable(false);\n\
            delEnable(false);\n\
\n\
            const aMsgs = messages.split('~');\n\
\n\
            aMsgs.forEach( (m) => {\n\
                if (! m )\n\
                    return;\n\
                const a = m.split('^');\n\
                const msg = a[1];\n\
                const par = a[0];\n\
                const p = par.split('`');\n\
                addRow([\n\
                    msg,\n\
                    p[0],\n\
                    p[1],\n\
                    p[3],\n\
                    p[4],\n\
                ]);\n\
            });\n\
        });\n\
\n\
    </script>\n\
\n\
</body>\n\
</html>\n"
};


#endif
