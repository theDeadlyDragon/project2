let irLeft = document.querySelector('#irLeft');
let irRight = document.querySelector('#irRight');
let state = document.querySelector('#state');
let ultrasoon = document.querySelector('#ultrasoon');
let reed = document.querySelector('#reed');

var xmlHttp = new XMLHttpRequest();
var response;

var irLeftState;
var irRightState;
var state2;
var ultrasoonState;
var reedState;

function loader(){
    httpGetSync("/sensor");
    updateScreen();
}

function updateScreen(){
    if(irLeftState == "0"){
        irLeft.innerHTML = "InfraRed Left: FALSE";
        irLeft.classList.remove("active");
    }
    else{
        irLeft.innerHTML = "InfraRed Left: TRUE";
        irLeft.classList.add("active");
    }

    if(irRightState == "0"){
        irRight.innerHTML = "InfraRed Right: FALSE";
        irRight.classList.remove("active");
    }
    else{
        irRight.innerHTML = "InfraRed Right: TRUE";
        irRight.classList.add("active");
    }

    if(reedState == "0"){
        reed.innerHTML = "Reed: FALSE";
        reed.classList.remove("active");
    }
    else{
        reed.innerHTML = "Reed: TRUE";
        reed.classList.add("active");
    }

    ultrasoon.innerHTML = "Ultrasoon: " + ultrasoonState;

    switch(state2){
        case "0":
            state.innerHTML = "Current State: IDLE";
            break;
        case "1":
            state.innerHTML = "Current State: MANUAL";
            break;
        case "2":
            state.innerHTML = "Current State: AUTOPILOT";
            break;
        case "3":
            state.innerHTML = "Current State: OBJECT AVOIDANCE";
            break;
    }
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
            irLeftState = xmlHttp.getResponseHeader("irLeft");
            irRightState = xmlHttp.getResponseHeader("irRight");
            state2 = xmlHttp.getResponseHeader("state");
            ultrasoonState = xmlHttp.getResponseHeader("ultrasoon");
            reedState = xmlHttp.getResponseHeader("reed");
        }
    }
    xmlHttp.open("GET", url, false); // true for asynchronous 
    xmlHttp.send(null);
}