const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');

// Set canvas size
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

// Load images
const basketImage = new Image();
basketImage.src = 'D:/game củ cải/images/55e8801d-fb88-45af-b394-2c7224fd22de.jpg'; // Đặt đường dẫn đúng
const ballImage = new Image();
ballImage.src = 'D:/game củ cải/images/18c780ab-f751-41bc-8ff5-196b196f19a3-removebg-preview.png';
const heartImage = new Image();
heartImage.src = 'D:/game củ cải/images/74133f5f-f8bd-41ec-a151-de0f730f8252-removebg-preview.png';

const basket = {
    x: canvas.width / 2 - 75,
    y: canvas.height - 100,
    width: 150,
    height: 50,
    speed: 10
};

const items = [];
const keys = {};
let score = 0;
let lives = 3; // Number of lives
let gameRunning = true;

// Listen to keyboard events
document.addEventListener('keydown', (event) => {
    keys[event.key.toLowerCase()] = true;
});

document.addEventListener('keyup', (event) => {
    keys[event.key.toLowerCase()] = false;
});

// Generate new falling items periodically
setInterval(() => {
    if (gameRunning) {
        items.push({
            x: Math.random() * (canvas.width - 40),
            y: 0,
            radius: 20,
            speed: Math.random() * 3 + 2,
            image: ballImage
        });
    }
}, 1000);

function drawBasket() {
    ctx.drawImage(basketImage, basket.x, basket.y, basket.width, basket.height);
}

function drawItems() {
    items.forEach(item => {
        ctx.drawImage(item.image, item.x - item.radius, item.y - item.radius, item.radius * 2, item.radius * 2);
    });
}

function drawHearts() {
    const heartSize = 30;
    for (let i = 0; i < lives; i++) {
        ctx.drawImage(heartImage, 10 + i * (heartSize + 5), 10, heartSize, heartSize);
    }
}

function moveBasket() {
    if (keys['a'] && basket.x > 0) basket.x -= basket.speed;
    if (keys['d'] && basket.x + basket.width < canvas.width) basket.x += basket.speed;
}

function moveItems() {
    items.forEach((item, index) => {
        item.y += item.speed;

        // Check for missed item
        if (item.y - item.radius > canvas.height) {
            items.splice(index, 1);
            lives -= 1; // Decrease lives
            if (lives <= 0) {
                gameRunning = false;
            }
        }

        // Check for caught item
        if (
            item.y + item.radius > basket.y &&
            item.x > basket.x &&
            item.x < basket.x + basket.width
        ) {
            items.splice(index, 1);
            score += 1;
        }
    });
}

function updateGame() {
    if (!gameRunning) {
        ctx.fillStyle = 'red';
        ctx.font = '48px Arial';
        ctx.fillText('Game Over', canvas.width / 2 - 100, canvas.height / 2);
        return;
    }

    ctx.clearRect(0, 0, canvas.width, canvas.height);
    
    // Draw game elements
    drawBasket();
    drawItems();
    drawHearts();
    moveBasket();
    moveItems();

    // Draw score
    ctx.fillStyle = 'white';
    ctx.font = '24px Arial';
    ctx.fillText(`Score: ${score}`, 20, 70);

    requestAnimationFrame(updateGame);
}

// Start the game when images are loaded
basketImage.onload = () => {
    ballImage.onload = () => {
        heartImage.onload = () => {
            updateGame();
        };
    };
};

// Resize canvas on window resize
window.addEventListener('resize', () => {
    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;
    basket.y = canvas.height - 100;
});
