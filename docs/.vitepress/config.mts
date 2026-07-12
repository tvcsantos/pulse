import { defineConfig } from 'vitepress'

export default defineConfig({
  title: 'Pulse',
  description: 'Arduino Ultrasonic Parking Sensor',
  base: '/pulse/',
  lastUpdated: true,

  head: [
    ['link', { rel: 'icon', href: '/pulse/icon-dark.png' }],
    ['meta', { property: 'og:title', content: 'Pulse - Arduino Ultrasonic Parking Sensor' }],
    ['meta', { property: 'og:description', content: 'A DIY garage parking sensor built with an Arduino, an ultrasonic sensor and a 12V LED semaphore.' }],
    ['meta', { property: 'og:image', content: 'https://tvcsantos.github.io/pulse/img/pulse-build.jpeg' }],
    ['meta', { property: 'og:url', content: 'https://tvcsantos.github.io/pulse/' }]
  ],

  themeConfig: {
    logo: {
      light: '/icon-dark.png',
      dark: '/icon-light.png'
    },

    nav: [
      { text: 'Overview', link: '/' },
      { text: 'The sketch', link: '/code' }
    ],

    socialLinks: [
      { icon: 'github', link: 'https://github.com/tvcsantos/pulse' }
    ],

    editLink: {
      pattern: 'https://github.com/tvcsantos/pulse/blob/main/docs/:path'
    },

    footer: {
      copyright: 'Copyright 2016 Tiago Santos'
    }
  }
})
