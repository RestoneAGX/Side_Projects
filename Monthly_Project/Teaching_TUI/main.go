package main

import (
    "log"
    tea "github.com/charmbracelet/bubbletea"
)

type model struct{}

func initModel() model{
    return model{
    };
}

func (m model) Init() tea.Cmd{
    // *TODO: Load the starting menu Text | Setup maps | Load save file
    return nil
}

func (m model) Update(msg tea.Msg) (tea.Model, tea.Cmd){
    switch msg := msg.(type) {
        case tea.KeyMsg:
            switch msg.String() {
                case "ctrl+c", "q":
                    return m, tea.Quit
            }
    }

    return m, nil
}

func (m model) View() (output string) {
 return;
}

func main(){
    p := tea.NewProgram(initModel())
    if _, err := p.Run(); err != nil{
        log.Fatal(err);
    }
}
