const canvas = document.querySelector('canvas');
const ctx = canvas.getContext('2d');

canvas.height = window.innerHeight;
canvas.width = window.innerWidth;

window.onresize = function(e) {
  canvas.height = window.innerHeight;
  canvas.width = window.innerWidth;
}

canvas.style.backgroundColor = '#334';
document.body.style.padding = '0';
document.body.style.margin = '0';
document.body.style.overflow = 'hidden';

const time = {
	deltaTime: 0
}