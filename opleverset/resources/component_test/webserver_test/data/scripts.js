async function ledLeft() {
    await fetch("/left", { method: "POST" });
}

async function ledRight() {
    await fetch("/right", { method: "POST" });
}

async function stopLeft() {
    await fetch("/stopL", { method: "POST" });
}

async function stopRight() {
    await fetch("/stopR", { method: "POST" });
}