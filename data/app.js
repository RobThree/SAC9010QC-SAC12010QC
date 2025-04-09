// Configuration
const API_ENDPOINT = "/state";

// AC state
let acState = {
  power: false,
  temperature: 20,
  fanspeed: 0,
  mode: "COOL",
  swing: false,
  sleep: false,
  humid: false,
  light: false,
  ionizer: false,
  save: false,
  timer: 0,
};

// DOM elements
const powerBtn = document.getElementById("powerBtn");
const tempValue = document.getElementById("tempValue");
const tempUp = document.getElementById("tempUp");
const tempDown = document.getElementById("tempDown");
const modeSelect = document.getElementById("modeSelect");
const fanSpeedSelect = document.getElementById("fanSpeedSelect");
const swingBtn = document.getElementById("swingBtn");
const sleepBtn = document.getElementById("sleepBtn");
const humidBtn = document.getElementById("humidBtn");
const lightBtn = document.getElementById("lightBtn");
const ionizerBtn = document.getElementById("ionizerBtn");
const saveBtn = document.getElementById("saveBtn");
const timerHours = document.getElementById("timerHours");
const timerUp = document.getElementById("timerUp");
const timerDown = document.getElementById("timerDown");
const submitBtn = document.getElementById("submitBtn");
const refreshBtn = document.getElementById("refreshBtn");
const statusMsg = document.getElementById("statusMsg");
const controlsContainer = document.getElementById("controlsContainer");

// Function to update UI based on current state
function updateUI() {
  // Power button
  if (acState.power) {
    powerBtn.classList.add("on");
  } else {
    powerBtn.classList.remove("on");
  }

  // Temperature
  tempValue.textContent = acState.temperature;

  // Mode and Fan Speed
  modeSelect.value = acState.mode;
  fanSpeedSelect.value = acState.fanspeed.toString();

  // Toggle buttons
  updateToggleButton(swingBtn, acState.swing);
  updateToggleButton(sleepBtn, acState.sleep);
  updateToggleButton(humidBtn, acState.humid);
  updateToggleButton(lightBtn, acState.light);
  updateToggleButton(ionizerBtn, acState.ionizer);
  updateToggleButton(saveBtn, acState.save);

  // Timer
  const hours = acState.timer * 0.5;
  timerHours.textContent = hours + (hours === 1 ? " hr" : " hrs");
}

function updateToggleButton(button, isActive) {
  if (isActive) {
    button.classList.add("active");
  } else {
    button.classList.remove("active");
  }
}

// Function to fetch current AC state
async function fetchACState() {
  const overlay = document.getElementById("loadingOverlay");

  try {
    const response = await fetch(API_ENDPOINT);
    overlay.classList.remove("hidden");
    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }
    acState = await response.json();
    updateUI();
    overlay.classList.add("hidden");
    showStatus("Connected to AC controller", "success");
  } catch (error) {
    console.error("Error fetching AC state:", error);
    showStatus("Failed to connect to AC controller", "error");
  }
}

// Function to send updated AC state
async function sendACState() {
  try {
    const response = await fetch(API_ENDPOINT, {
      method: "PUT",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(acState),
    });

    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }

    showStatus("Settings applied successfully", "success");
  } catch (error) {
    console.error("Error updating AC state:", error);
    showStatus("Failed to apply settings", "error");
  }
}

// Function to show status messages
function showStatus(message, type) {
  statusMsg.textContent = message;
  statusMsg.className = "status " + type;
  statusMsg.classList.remove("hidden");

  setTimeout(() => {
    statusMsg.classList.add("hidden");
  }, 3000);
}

// Event Listeners
powerBtn.addEventListener("click", () => {
  acState.power = !acState.power;
  updateUI();
});

tempUp.addEventListener("click", () => {
  if (acState.temperature < 30) {
    acState.temperature++;
    updateUI();
  }
});

tempDown.addEventListener("click", () => {
  if (acState.temperature > 16) {
    acState.temperature--;
    updateUI();
  }
});

modeSelect.addEventListener("change", (e) => {
  acState.mode = e.target.value;
});

fanSpeedSelect.addEventListener("change", (e) => {
  acState.fanspeed = parseInt(e.target.value);
});

swingBtn.addEventListener("click", () => {
  acState.swing = !acState.swing;
  updateUI();
});

sleepBtn.addEventListener("click", () => {
  acState.sleep = !acState.sleep;
  updateUI();
});

humidBtn.addEventListener("click", () => {
  acState.humid = !acState.humid;
  updateUI();
});

lightBtn.addEventListener("click", () => {
  acState.light = !acState.light;
  updateUI();
});

ionizerBtn.addEventListener("click", () => {
  acState.ionizer = !acState.ionizer;
  updateUI();
});

saveBtn.addEventListener("click", () => {
  acState.save = !acState.save;
  updateUI();
});

timerUp.addEventListener("click", () => {
  if (acState.timer < 48) {
    acState.timer++;
    updateUI();
  }
});

timerDown.addEventListener("click", () => {
  if (acState.timer > 0) {
    acState.timer--;
    updateUI();
  }
});

submitBtn.addEventListener("click", sendACState);
refreshBtn.addEventListener("click", fetchACState);

// Initialize the app
document.addEventListener("DOMContentLoaded", fetchACState);
