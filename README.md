The point of writing this compiler was to understand how a compiler works on every level. From tokenizing to emitting assembly. It took a lot of iterations and hard resets to finally get to a point where I built something remotely scalable. 

The compiler is nowhere near finished or in any shape to do anything. I built keeping the "Make First, Perfect Later" mindset and I have gotten to a point where I think I can see a refactor on the horizon. 

As I am writing everything, even the part that generates the assembly. The compiler only supports computers on Apple silicon (technically it can support all ARM processors, but writing assembly on the M-series is slightly different.

Yes I have to use lldb, because I also need to implement a print statement from scratch.

Here's what the compiler can do:-
- 


  - Declare and define variable (they have to be done seperately).
<img width="420" height="129" alt="Screenshot 2025-08-06 at 10 42 51 PM" src="https://github.com/user-attachments/assets/e1eb8a82-752e-43d4-ab40-e964befc8554" />
<img width="929" height="112" alt="Screenshot 2025-08-06 at 10 39 49 PM" src="https://github.com/user-attachments/assets/b5758bb2-c9b6-43ea-82f6-092db51cfc83" />
<img width="387" height="178" alt="Screenshot 2025-08-06 at 10 54 02 PM" src="https://github.com/user-attachments/assets/a1c097fc-4c0b-4b34-8396-93dd41d042b8" />
<img width="728" height="134" alt="Screenshot 2025-08-06 at 10 50 49 PM" src="https://github.com/user-attachments/assets/e407384f-118f-4eda-b076-24771b67b8e6" />

  - Do basic arithmetic, addition and subtraction.

<img width="660" height="231" alt="Screenshot 2025-08-06 at 11 19 24 PM" src="https://github.com/user-attachments/assets/1fd3464b-b933-4a92-bc7c-1c703ab1f811" />
<img width="727" height="125" alt="Screenshot 2025-08-06 at 11 22 22 PM" src="https://github.com/user-attachments/assets/885cb3c4-7454-4820-802b-24ecf6cfbf69" />




  - Can process conditional statements (a > b; etc), but these were planned to be released with if and while statement's implementation, so they have no use right now.
