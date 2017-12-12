const express = require('express')

const app = express()
app.get('/', (req, res) => res.json({working: true}))

app.listen(8080, '0.0.0.0')