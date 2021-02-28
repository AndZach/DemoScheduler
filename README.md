# DemoScheduler

Υλοποίηση σε C ενός συστήματος χρονοπρογραμματισμού διεργασιών σε Linux. Το σύστημα θα
εκτελέσει το χρονοπρογραμματισμό 50 τυχαίων διεργασιών με χρήση του
Διαχειριστή Διεργασιών (γεννήτρια περιγραφέων διεργασιών): Μη-Αλληλεπιδραστικός Διαχειριστή Διεργασιών (NIPA), και στη συνέχεια του Χρονοπρογραμματιστή: Χρονοπρογραμματιστής Προτεραιοτήτων με FIFO (PrioritySchedulerFIFO). 

## Μη-Αλληλεπιδραστικός Διαχειριστής Διεργασιών (NonInteractiveProcessAdministrator - NIPA)
1. Τρέχει σε επαναληπτικό βρόχο (μέχρις ότου συμπληρωθούν 50 διεργασίες):
a. Κοιμάται (sleep) για ένα τυχαίο χρονικό διάστημα από 1 έως 10 second.
b. Δημιουργεί ένα τυχαίο αριθμό περιγραφέων διεργασιών (process descriptors)
(από 1 έως 10) με τη σειρά.
c. Για κάθε διεργασία:
I. δημιουργεί το μοναδικό αναγνωριστικό (id), τη διάρκεια εκτέλεσης
(duration),, την προτεραιότητα (priority). Η διάρκεια εκτέλεσης θα
πρέπει να κυμαίνεται στο διάστημα 5-30 sec, η προτεραιότητα από 1
εως 5. Μικρότερη τιμή σηματοδοτεί μεγαλύτερη προτεραιότητα, δηλαδή
η υψηλότερη προτεραιότητα είναι η 1.
II. Αποθηκεύει τα παραπάνω στοιχεία για κάθε διεργασία σε μια δομή
τύπου struct με όνομα procDesc..
III. Αποθηκεύει τη δομή σε λίστα (buffer) >50 θέσεων με σειρά FIFO.
2. Όταν τερματίσει επιστρέφει το buffer.

## Χρονοπρογραμματιστής Προτεραιοτήτων με FIFO (PrioritySchedulerFIFO)
1. Διατηρεί (αφού κάνει τις απαραίτητες αρχικοποιήσεις)
a. Πέντε διασυνδεδεμένες λίστες, inputProcessList<i> μία για κάθε κατηγορία
προτεραιότητας i. Η κάθε μια από τις λίστες αυτές περιέχει τους περιγραφείς
διεργασιών (procDesc) που έχουν την αντίστοιχη προτεραιότητα.
b. Μία λίστα terminatedProcessList, η οποία θα περιέχει τους περιγραφείς
διεργασιών που έχουν ολοκληρωθεί.
2. Παίρνει σαν είσοδο το buffer και τον αντιγράφει στις inputProcessList<i>
βάζοντας στην κάθε λίστα τη διεργασία εκείνη με προτεραιότητα i. Εαν υπάρχουν
διεργασίες με την ίδια προτεραιότητα χρησιμοποιεί τον FCFS για να επιλύσει τις
διαφορές.
3. Όσο υπάρχουν περιγραφείς διεργασιών σε κάποια από τις inputProcessList<i>:
a. Για κάθε κατηγορία προτεραιότητας, για κάθε διεργασία, ξεκινώντας από τη
κεφαλή της λίστας, φτιάχνει μια διεργασία testProcess με παραμέτρους <id,
duration, priority> και την εκτελεί.
b. Περιμένει εως ότου να τερματίσει η εκτέλεση της διεργασίας και στη συνέχεια
αντιγράφει τον περιγραφέα διεργασίας στη λίστα terminatedProcessList
c. Σε περίπτωση που προκύψει κάποιο σφάλμα στην εκτέλεση της διεργασίας ο
χρονοπρογραμματιστής επιστρέφει και τυπώνει μήνυμα λάθους μαζί με το
κωδικό λάθους που επέστρεψε η εκτέλεση της διεργασίας
4. Εναλλακτικά, όταν τερματίσει ο χρονοπρογραμματιστής, επιστρέφει τη
terminatedProcessList

## Διεργασία testProcess
Για κάθε περιγραφέα διεργασίας που περιλαμβάνεται στη δομή procDesc ο
χρονοπρογραμματιστής θα δημιουργήσει μια διεργασία testProcess η οποία τυπώνει
στην οθόνη το εξής μήνυμα:
“Hello World. Process <id>, duration <duration>, priority <priority>.”
όπου id, duration, priority είναι το μοναδικό αναγνωριστικό, η διάρκεια εκτέλεσης
και η προτεραιότητα που περιλαμβάνονται στη δομή procDesc.

Στη συνέχεια θα καθυστερεί η εκτέλεσή της της διεργασίας μέσω ενός βρόχου
επανάληψης:
r = (int) (double)rand() / ((double) RAND_MAX);
for (i=1;i<r*10000000;i++);
όπου r είναι ακέραια μεταβλητή, rand() είναι γεννήτρια τυχαίων αριθμών και
RAND_MAX είναι σταθερά του συστήματος ίση με 32767.

Η δημιουργία της διεργασίας testProcess που αντιστοιχεί στον περιγραφέα διεργασίας,
γίνεται μέσω των κλήσεων συστήματος fork() και execve().


