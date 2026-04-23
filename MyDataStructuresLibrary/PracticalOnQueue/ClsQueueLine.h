#pragma once

#include <iostream>
using namespace std;

#include "../Linear/ClsMyQueueArr.h";


namespace PracticalOnQueue
{
	class ClsQueueLine
	{
	private:

		struct stTicket
		{
			string DateAndTime;
			int WaitingClients;
			int WaitingTime;
			int MyNumber;
		};


		ClsMyQueueArr <stTicket> _queue;

		string _Prefix;
		short _AverageServeTime;
		int _ServedClients;
		int _NumberOfClients;


		string _GetCurrentDateAndTime()
		{
			time_t Time = time(0);

			tm* t = localtime(&Time);

			int hour = t->tm_hour;
			string AMOrPM = "AM";
			if (hour == 0)
			{
				hour = 12;
				AMOrPM = "AM";
			}
			else if (hour > 12)
			{
				hour -= 12;
				AMOrPM = "PM";
			}

			string DateAndTime = to_string(t->tm_wday) + "/" + to_string(t->tm_mon + 1) + "/" + to_string(t->tm_year + 1900) + " - " +
				to_string(hour) + ":" + to_string(t->tm_min) + ":" + to_string(t->tm_sec) + " " + AMOrPM;

			return DateAndTime;
		}

		string _GetCorrectWaitingTime(int WaitingTimeAsMinutes)
		{
			if (WaitingTimeAsMinutes >= 60)
			{
				short hour = WaitingTimeAsMinutes / 60;
				short minutes = WaitingTimeAsMinutes % 60;

				if (minutes == 0)
				{
					return to_string(hour) + " Hour";
				}
				else
				{
					return to_string(hour) + " Hour : " + to_string(minutes) + " Minutes";
				}
			}
			else
			{
				return to_string(WaitingTimeAsMinutes) + " Minutes";
			}
		}

		void _PrintOneTicket(stTicket ticket)
		{
			cout << "\n\n\t\t\t----------------------------------\n\n";

			cout << "\t\t\t\t\t" << _Prefix << ticket.MyNumber;

			cout << "\n\n\t\t\t\t" << ticket.DateAndTime << "\n";
			cout << "\t\t\t\t " << "WaitingClients = " << ticket.WaitingClients << "\n";
			cout << "\t\t\t\t   " << "Serve Time In" << "\n";
			cout << "\t\t\t\t    " << _GetCorrectWaitingTime(ticket.WaitingTime);

			cout << "\n\n\t\t\t----------------------------------\n\n";
		}


	public:


		ClsQueueLine(string Prefix, short ServeTime)
		{
			_Prefix = Prefix;
			_AverageServeTime = ServeTime;
			_ServedClients = 0;
			_NumberOfClients = 0;
		}

		void IssueTicket()
		{
			_NumberOfClients++;
			if (_NumberOfClients > 1)
				_queue.Push(stTicket{ _GetCurrentDateAndTime() , _NumberOfClients - 1 , _NumberOfClients * _AverageServeTime , _NumberOfClients });
			else if (_NumberOfClients == 1)
				_queue.Push(stTicket{ _GetCurrentDateAndTime() , _NumberOfClients - 1 , _AverageServeTime , _NumberOfClients });
		}

		void PrintInfo()
		{
			cout << "\n\n\n\t\t\t-------------------------------\n\n";
			cout << "\t\t\t\tQueue Info";
			cout << "\n\n\t\t\t-------------------------------\n\n";

			cout << "\t\t\t  Prefix          = " << _Prefix << "\n";
			cout << "\t\t\t  Total Tickets   = " << _NumberOfClients << "\n";
			cout << "\t\t\t  Served Clients  = " << _ServedClients << "\n";
			cout << "\t\t\t  Waiting Clients = " << _queue.Size() << "\n";

			cout << "\n\t\t\t-------------------------------\n\n";
		}

		void PrintTicketsLineRtoL()
		{
			cout << "\n\n\t\tTickets:  ";

			for (int i = 0; i < _queue.Size(); i++)
			{
				cout << _Prefix << _queue.GetItem(i).MyNumber << " <-- ";
			}

			cout << "\n\n";
		}

		void PrintTicketsLineLtoR()
		{
			cout << "\n\n\t\tTickets:  ";

			for (int i = _queue.Size() - 1; i >= 0; i--)
			{
				cout << _Prefix << _queue.GetItem(i).MyNumber << " --> ";
			}

			cout << "\n\n";
		}

		void PrintAllTickets()
		{
			cout << "\n\n\t\t\t\t  ---Tickets---\n";

			for (int i = 0; i < _queue.Size(); i++)
			{
				_PrintOneTicket(_queue.GetItem(i));
			}

		}

		void ServeNextClient()
		{
			if (!_queue.IsEmpty())
			{
				_ServedClients++;
				_queue.Pop();
			}
		}

		string WhoIsNext()
		{
			if (_queue.IsEmpty())
			{
				return "\nNo Clients Found!\n";
			}
			else
			{
				return _Prefix + to_string(_queue.GetFront().MyNumber);
			}
		}


	};
}


// This is an example of how to test this class in the main function 

//int main()
//{
//	ClsQueueLine PayBillsQueue("A0", 10);
//	ClsQueueLine SubscriptionsQueue("B0", 5);
//
//	PayBillsQueue.IssueTicket();
//	PayBillsQueue.IssueTicket();
//	PayBillsQueue.IssueTicket();
//	PayBillsQueue.IssueTicket();
//	PayBillsQueue.IssueTicket();
//
//
//	cout << "\nPay Bills Queue Info:\n";
//	PayBillsQueue.PrintInfo();
//
//	PayBillsQueue.PrintTicketsLineRtoL();
//	PayBillsQueue.PrintTicketsLineLtoR();
//
//
//	PayBillsQueue.PrintAllTickets();
//
//	PayBillsQueue.ServeNextClient();
//
//
//	cout << "\nPay Bills Queue After Serve One Client\n";
//	PayBillsQueue.PrintInfo();
//
//
//	cout << "\n====================================================================================================\n";
//
//	cout << "\n\n\t\t\t\tSubscriptions Queue:\n\n";
//
//
//
//	SubscriptionsQueue.IssueTicket();
//	SubscriptionsQueue.IssueTicket();
//	SubscriptionsQueue.IssueTicket();
//	SubscriptionsQueue.IssueTicket();
//
//
//	cout << "\n\nSubscriptions Queue Info:\n";
//	SubscriptionsQueue.PrintInfo();
//
//	SubscriptionsQueue.PrintTicketsLineRtoL();
//	SubscriptionsQueue.PrintTicketsLineLtoR();
//
//
//	SubscriptionsQueue.PrintAllTickets();
//
//	SubscriptionsQueue.ServeNextClient();
//
//
//	cout << "\nSubscriptions Queue After Serve One Client\n";
//	SubscriptionsQueue.PrintInfo();
//
//	return 0;
//}

