package main

import (
	"log"
	"net/http"

	"github.com/maxence-charriere/go-app/v9/pkg/app"
)



type hello struct{
	app.Compo
}

func (h* hello) Render() app.UI {
	return app.H1().Text("Hello World")
}

func main(){
	app.Route("/", &hello{})

	go app.RunWhenOnBrowser()

	http.Handle("/", &app.Handler {
		Name: "Hello",
		Description: "",
	})

	if err := http.ListenAndServe(":8000", nil); err != nil {
		log.Fatal(err)
	}
}