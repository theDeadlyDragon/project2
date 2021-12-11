let buttonS = document.querySelector('#startButton');
var xmlHttp = new XMLHttpRequest();
var response;

function loader(){
    httpGetSync("/state");

    if(response == "0"){
        buttonS.innerText = "Start";
    }
    else{
        buttonS.innerText = "Stop";
    }  
}

function toggle(){
    if(buttonS.innerText == "Start"){
        buttonS.innerText = "Stop";
    }
    else{
        buttonS.innerText = "Start";
    }
    httpGetAsync("/startStop");
}

async function go() {
    await fetch("/go", { method: "POST" });
}

async function back() {
    await fetch("/back", { method: "POST" });
}

async function right() {
    await fetch("/right", { method: "POST" });
}

async function left() {
    await fetch("/left", { method: "POST" });
}

async function stop() {
    await fetch("/stop", { method: "POST" });
}

async function startStop() {
    await fetch("/startStop", { method: "POST" });
}

function httpGetAsync(url){
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() { 
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200){
            response = xmlHttp.responseText;
        }
    }
    xmlHttp.open("GET", url, true); // true for asynchronous 
    xmlHttp.send(null);
}

function httpGetSync(url){
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() { 
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200){
            response = xmlHttp.responseText;
        }
    }
    xmlHttp.open("GET", url, false); // true for asynchronous 
    xmlHttp.send(null);
}